/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_mesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <dbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 14:24:19 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/10 12:28:38 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct	s_vector
{
	double		x_step;
	double		y_step;
}				t_vector;

int			ft_nb_lines(int **mesh)
{
	int		i;

	i = 0;
	while (mesh[i])
		i++;
	return (i);
}

t_vector	*ft_new_vector(double x, double y)
{
	t_vector	*res;

	if (!(res = (t_vector*)malloc(sizeof(t_vector))))
		return (NULL);
	res->x_step = x;
	res->y_step = y;
	return (res);
}

double		ft_invert(double inp)
{
	return (1.0 - inp);
}

int			ft_render_mesh(void *mlx_param)
{
	int			y;
	int			x;
	double		current_x;
	double		current_y;
	t_vector	*dev;
	t_pov		*pov;
	t_mlx		*mlx;
	int			**mesh;

	mlx = (t_mlx*)mlx_param;
	mesh = mlx->mesh;
	mlx->pov->head_balance += 0.1;
	pov = mlx->pov;
	double	min;

	min = (double)((double)(HEIGHT) * 0.5 / ft_nb_lines(mesh));
	if (min > (double)(((double)WIDTH) * 0.5 / mesh[0][0]))
		min = (double)(((double)WIDTH) * 0.5 / mesh[0][0]);
	dev = ft_new_vector(sin(pov->head_balance * RAD) * min, cos(pov->head_balance * RAD) * min);
	y = 0;
	while (mesh[y + 1])
	{
		x = 1;
		current_x = WIDTH * 0.25 - (y * dev->y_step);
		current_y = HEIGHT * 0.25 + (y * dev->x_step);
		while (x < mesh[y][0])
		{
			ft_draw_rect(mlx, ft_new_rect(
					ft_new_point(current_x, current_y, mesh[y][x]),
					ft_new_point(current_x + dev->x_step, current_y + dev->y_step, mesh[y][x + 1]),
					ft_new_point(current_x + dev->x_step - dev->y_step, current_y + dev->y_step + dev->x_step, mesh[y + 1][x + 1]),
					ft_new_point(current_x - dev->y_step, current_y + dev->x_step, mesh[y + 1][x])
										), ft_get_color);
			current_x += dev->x_step;
			current_y += dev->y_step;
			x++;
		}
		y++;
	}
	return (0);
}
