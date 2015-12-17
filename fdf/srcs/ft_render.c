/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 14:09:05 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/17 17:42:40 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		get_coords_at_xy(t_mlx *mlx, int y, int x, t_vector *dev)
{
	mlx->points[y][x - 1]->height = mlx->mesh[y][x];
	if (mlx->view_mode == 0)
	{
		mlx->points[y][x - 1]->x = mlx->start_x - y * dev->y_step
			+ x * dev->x_step;
		mlx->points[y][x - 1]->y = mlx->start_y + y * dev->x_step
			* mlx->elevation + x * mlx->elevation * dev->y_step
			- mlx->mesh[y][x] * mlx->unit / mlx->height_factor;
	}
	else
	{
		mlx->points[y][x - 1]->x = mlx->start_x - y * dev->y_step
			+ x * dev->y_step;
		mlx->points[y][x - 1]->y = mlx->start_y + y * dev->x_step + x
			* dev->x_step - mlx->mesh[y][x] * mlx->unit / mlx->height_factor;
	}
}

double		get_extreme_y(t_mlx *mlx, int nb_lines)
{
	double	smaller;
	double	higher;

	smaller = mlx->points[0][0]->y;
	higher = mlx->points[0][0]->y;
	if (mlx->points[0][mlx->mesh[0][0] - 1]->y < smaller)
		smaller = mlx->points[0][mlx->mesh[0][0] - 1]->y;
	else if (mlx->points[0][mlx->mesh[0][0] - 1]->y > higher)
		higher = mlx->points[0][mlx->mesh[0][0] - 1]->y;
	if (mlx->points[nb_lines][mlx->mesh[nb_lines][0] - 1]->y < smaller)
		smaller = mlx->points[nb_lines][mlx->mesh[nb_lines][0] - 1]->y;
	else if (mlx->points[nb_lines][mlx->mesh[nb_lines][0] - 1]->y > higher)
		higher = mlx->points[nb_lines][mlx->mesh[nb_lines][0] - 1]->y;
	if (mlx->points[nb_lines][0]->y < smaller)
		smaller = mlx->points[nb_lines][0]->y;
	else if (mlx->points[nb_lines][0]->y > higher)
		higher = mlx->points[nb_lines][0]->y;
	return ((smaller + higher) / 2.0);
}

double		get_extreme_x(t_mlx *mlx, int nb_lines)
{
	double	smaller;
	double	higher;

	smaller = mlx->points[0][0]->x;
	higher = mlx->points[0][0]->x;
	if (mlx->points[0][mlx->mesh[0][0] - 1]->x < smaller)
		smaller = mlx->points[0][mlx->mesh[0][0] - 1]->x;
	else if (mlx->points[0][mlx->mesh[0][0] - 1]->x > higher)
		higher = mlx->points[0][mlx->mesh[0][0] - 1]->x;
	if (mlx->points[nb_lines][mlx->mesh[nb_lines][0] - 1]->x < smaller)
		smaller = mlx->points[nb_lines][mlx->mesh[nb_lines][0] - 1]->x;
	else if (mlx->points[nb_lines][mlx->mesh[nb_lines][0] - 1]->x > higher)
		higher = mlx->points[nb_lines][mlx->mesh[nb_lines][0] - 1]->x;
	if (mlx->points[nb_lines][0]->x < smaller)
		smaller = mlx->points[nb_lines][0]->x;
	else if (mlx->points[nb_lines][0]->x > higher)
		higher = mlx->points[nb_lines][0]->x;
	return ((smaller + higher) / 2.0);
}

void		mesh_to_points(t_mlx *mlx)
{
	int		y;
	int		x;
	int		nb_lines;
	t_vector	*dev;

	if (mlx->view_mode != 1)
		dev = ft_new_vector(sin(mlx->angle * RAD) * mlx->unit
				, cos(mlx->angle * RAD) * mlx->unit);
	else
		dev = ft_new_vector(sin(30 * RAD) * mlx->unit
				, cos(30 * RAD) * mlx->unit);
	nb_lines = ft_nb_lines(mlx->mesh);
	set_start_point(mlx, dev, nb_lines - 1);
	y = 0;
	while (y < nb_lines)
	{
		x = 1;
		while (x <= mlx->mesh[y][0])
		{
			get_coords_at_xy(mlx, y, x, dev);
			x++;
		}
		y++;
	}
}

int			ft_render(void *mlx_param)
{
	t_mlx	*mlx;
	int		x;
	int		y;

	mlx = (t_mlx*)mlx_param;
	restore_window(mlx);
	mesh_to_points(mlx);
	y = 0;
	while (mlx->points[y + 1])
	{
		x = 0;
		while (mlx->points[y][x + 1])
		{
			ft_draw_void_rect(mlx, y, x);
			x++;
		}
		y++;
	}
	ft_put_image_to_window(mlx->mlx, mlx->win, mlx->img);
	return (0);
}
