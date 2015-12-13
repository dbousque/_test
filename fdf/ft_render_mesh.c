/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_mesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <dbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 14:24:19 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/11 14:14:19 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"












#include <stdio.h>

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

double		ft_get_min(t_mlx *mlx)
{
	double		min;
	int			nb_lines;

	nb_lines = ft_nb_lines(mlx->mesh);
	min = (double)((double)(HEIGHT) / mlx->pov->zoom / nb_lines);
	if (min > (double)(((double)WIDTH) / mlx->pov->zoom / nb_lines))
		min = (double)(((double)WIDTH) / mlx->pov->zoom / nb_lines);
	if (min > (double)(((double)HEIGHT) / mlx->pov->zoom / mlx->mesh[0][0]))
		min = (double)(((double)HEIGHT) / mlx->pov->zoom / mlx->mesh[0][0]);
	if (min > (double)(((double)WIDTH) / mlx->pov->zoom / mlx->mesh[0][0]))
		min = (double)(((double)WIDTH) / mlx->pov->zoom / mlx->mesh[0][0]);
	return (min);
}

void		ft_get_start_point(double *x_start, double *y_start, t_mlx *mlx, t_vector *dev)
{
	int		tab_height;
	int		tab_width;
	t_point	*tmp_pnt;

	tab_width = mlx->mesh[0][0];
	tab_height = ft_nb_lines(mlx->mesh);

	tmp_pnt = ft_new_point(WIDTH / 2 + ((tab_height - 1) / 2.0 * dev->y_step),
		   				HEIGHT / 2 - ((tab_height - 1) / 2.0 * dev->x_step), 0.0);
	*x_start = tmp_pnt->x - (((tab_width - 1) / 2.0) * dev->x_step);
	*y_start = tmp_pnt->y - (((tab_width - 1) / 2.0) * dev->y_step);
}

/*void		ft_draw_multicolumn_start(t_mlx *mlx, double start_x, double start_y, t_vector *dev)
{
	int		nb_lines;
	int		i;

	i = 0;
	nb_lines = ft_nb_lines(mlx->mesh);
	while (i < nb_lines)
	{
		ft_draw_line(mlx, ft_new_point(start_x, start_y), ft_new_point(start_x + dev->x_step, start_y + dev->y_step), ft_fet_color2);
		start_x += dev->y_step;
		start_y += dev->x_step;
		i++;
	}
}*/

void		ft_draw_multiline(t_mlx *mlx, double start_x, double start_y, t_vector *dev, int nb_lines)
{
	int		i;

	i = 1;
	while (i < (nb_lines == -1 ? mlx->mesh[0][0] : nb_lines))
	{
		ft_draw_line(mlx, ft_new_point(start_x, start_y, 0.0), ft_new_point(start_x + dev->x_step, start_y + dev->y_step, 0.0), ft_get_color2);
		start_x += dev->x_step;
		start_y += dev->y_step;
		i++;
	}
}

void		ft_draw_around_mesh(t_mlx *mlx, t_vector *dev, double start_x, double start_y, double min)
{
	int			nb_lines;
	t_vector	*inv_dev;

	nb_lines = ft_nb_lines(mlx->mesh);
	inv_dev = ft_new_vector(-sin(mlx->pov->head_balance * RAD) * min, cos(mlx->pov->head_balance * RAD) * min);
	ft_draw_multiline(mlx, start_x, start_y, dev, -1);
	ft_draw_multiline(mlx, start_x - (nb_lines - 1) * dev->y_step, start_y + (nb_lines - 1) * dev->x_step, dev, -1);
	ft_draw_multiline(mlx, start_x, start_y, inv_dev, nb_lines);
	ft_draw_multiline(mlx, start_x + (mlx->mesh[0][0] - 1) * dev->x_step, start_y + (mlx->mesh[0][0] - 1) * dev->y_step, inv_dev, nb_lines);
	//ft_draw_multicolum(mlx->mesh, 1, start_x, start_y, dev);
}

t_vector	*get_3d_dev(t_mlx *mlx)
{
	double		angle;
	double		hypothenuse;
	t_vector	*dev_3d;

	hypothenuse = sqrt(((mlx->pov->y - HEIGHT / 2) * (mlx->pov->y - HEIGHT / 2))
						+ (mlx->pov->height * mlx->pov->height));
	angle = mlx->pov->height / hypothenuse;
	printf("height : %f, hypo : %f\n", mlx->pov->height, hypothenuse);
	angle = asin(angle);
	dev_3d = ft_new_vector(1.0, sin(angle));
	printf("%f\n", angle / RAD);
	return (dev_3d);
}

//int			ft_render_mesh2(void *mlx_param)
//{
//	t_3d_vec	*pov_vec;
//	t_mlx		*mlx;

//	mlx = (t_mlx*)mlx_param;
	//pov_vec = get_pov_vec(mlx);
//}

int			ft_render_mesh(void *mlx_param)
{
	int			y;
	int			x;
	double		current_x;
	double		current_y;
	t_vector	*dev;
	t_vector	*dev_3d;
	t_mlx		*mlx;
	double		start_x;
	double		start_y;
	double		min;

	mlx = (t_mlx*)mlx_param;
	mlx->pov->y = mlx->height;
	mlx->pov->height = mlx->height / 2;
	//mlx->pov->zoom -= 0.005;
	//mlx->pov->head_balance += 0.7;

	restore_window(mlx);
	
	min = ft_get_min(mlx);
	dev_3d = get_3d_dev(mlx);
	dev = ft_new_vector(cos(mlx->pov->head_balance * RAD) * min, sin(mlx->pov->head_balance * RAD) * min);
	ft_get_start_point(&start_x, &start_y, mlx, dev);
	y = 0;
	while (mlx->mesh[y + 1])
	{
		x = 1;
		current_x = start_x - (y * dev->y_step);
		current_y = start_y + (y * dev->x_step);
		while (x < mlx->mesh[y][0])
		{
			ft_draw_rect(mlx, ft_new_rect(
					ft_new_point(current_x, current_y, mlx->mesh[y][x]),
					ft_new_point(current_x + dev->x_step, current_y + (dev->y_step), mlx->mesh[y][x + 1]),
					ft_new_point(current_x + dev->x_step - (dev->y_step), current_y + (dev->y_step + dev->x_step), mlx->mesh[y + 1][x + 1]),
					ft_new_point(current_x - dev->y_step, current_y + dev->x_step, mlx->mesh[y + 1][x])
										), ft_get_color);
			current_x += dev->x_step;
			current_y += dev->y_step;
			x++;
		}
		y++;
	}
	ft_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}
