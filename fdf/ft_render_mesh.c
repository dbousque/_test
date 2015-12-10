/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_mesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <dbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 14:24:19 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/10 19:02:07 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"












#include <stdio.h>



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

double		ft_get_min(int **mesh)
{
	double		min;

	min = (double)((double)(HEIGHT) * 0.5 / ft_nb_lines(mesh));
	if (min > (double)(((double)WIDTH) * 0.5 / ft_nb_lines(mesh)))
		min = (double)(((double)WIDTH) * 0.5 / ft_nb_lines(mesh));
	if (min > (double)(((double)HEIGHT) * 0.5 / mesh[0][0]))
		min = (double)(((double)HEIGHT) * 0.5 / mesh[0][0]);
	if (min > (double)(((double)WIDTH) * 0.5 / mesh[0][0]))
		min = (double)(((double)WIDTH) * 0.5 / mesh[0][0]);
	return (min);
}

void		ft_get_start_point(double *x_start, double *y_start, t_pov *pov, t_vector *dev, int **mesh, double min, t_mlx *mlx)
{
	int		tab_height;
	int		tab_width;
	t_point	*tmp_pnt;

	tab_width = mesh[0][0];
	tab_height = ft_nb_lines(mesh);

	tmp_pnt = ft_new_point(WIDTH / 2 + (   (  ((tab_height - 1) * min)   / 2.0) * sin(pov->head_balance * RAD)   ),
		   				HEIGHT / 2 - (     (  ((tab_height - 1) * min)   / 2.0) * cos(pov->head_balance * RAD)), 0.0);


	mlx_pixel_put(mlx->mlx, mlx->win, WIDTH / 2, HEIGHT / 2, 0x00FF00);
	mlx_pixel_put(mlx->mlx, mlx->win, WIDTH / 2 + 1, HEIGHT / 2, 0x00FF00);
	mlx_pixel_put(mlx->mlx, mlx->win, WIDTH / 2 - 1, HEIGHT / 2 + 1, 0x00FF00);
	mlx_pixel_put(mlx->mlx, mlx->win, WIDTH / 2 + 1, HEIGHT / 2 + 1, 0x00FF00);

	mlx_pixel_put(mlx->mlx, mlx->win, tmp_pnt->x, tmp_pnt->y, 0x0000FF);
	mlx_pixel_put(mlx->mlx, mlx->win, tmp_pnt->x + 1, tmp_pnt->y, 0x0000FF);
	mlx_pixel_put(mlx->mlx, mlx->win, tmp_pnt->x - 1, tmp_pnt->y + 1, 0x0000FF);
	mlx_pixel_put(mlx->mlx, mlx->win, tmp_pnt->x + 1, tmp_pnt->y + 1, 0x0000FF);


	*x_start = tmp_pnt->x - (((tab_width - 1) * min / 2.0) * cos(pov->head_balance * RAD));
	*y_start = tmp_pnt->y - (((tab_width - 1) * min / 2.0) * sin(pov->head_balance * RAD));
	   	
	
	mlx_pixel_put(mlx->mlx, mlx->win, *x_start, *y_start, 0xFFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, *x_start + 1, *y_start, 0xFFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, *x_start - 1, *y_start + 1, 0xFFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, *x_start + 1, *y_start + 1, 0xFFFFFF);

	//*x_start = WIDTH / 2 + (-dev->x_step * (((double)tab_width) / 2.0));
	//*y_start = HEIGHT / 2 + (-dev->y_step * (((double)tab_height) / 2.0));
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
	mlx->pov->head_balance += 0.01;
	pov = mlx->pov;
	double	min;

	min = ft_get_min(mesh);
	dev = ft_new_vector(cos(pov->head_balance * RAD) * min, sin(pov->head_balance * RAD) * min);
	//printf("%f, %f\n",dev->x_step, dev->y_step);
	y = 0;
	while (mesh[y + 1])
	{
		x = 1;
		ft_get_start_point(&current_x, &current_y, pov, dev, mesh, min, mlx);
		current_x -= (y * dev->y_step);
		current_y += (y * dev->x_step);
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
