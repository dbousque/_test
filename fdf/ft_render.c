/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 14:09:05 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/15 19:03:45 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"




#include <stdio.h>


int			ft_nb_lines(int **mesh)
{
	int		i;

	i = 0;
	while (mesh[i])
		i++;
	return (i);
}

void		ft_rem_img_from_window(void *mlx, void *win, void *img, int x, int y)
{
	int		*image;

	image = (int*)img;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (image[y * WIDTH + x])
				mlx_pixel_put(mlx, win, x, y, 0);
			x++;
		}
		y++;
	}
}

void		ft_put_image_to_window(void *mlx, void *win, void *img, int x, int y)
{
	int		*image;

	image = (int*)img;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (image[y * WIDTH + x])
				mlx_pixel_put(mlx, win, x, y, image[y * WIDTH + x]);
			x++;
		}
		y++;
	}
}

void		restore_window(t_mlx *mlx)
{
	ft_rem_img_from_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	ft_bzero(mlx->img, mlx->width * mlx->height * sizeof(int));
}

void		get_coords_at_xy(t_mlx *mlx, int y, int x, t_vector *dev)
{
	mlx->points[y][x - 1]->height = mlx->mesh[y][x];
	if (mlx->view_mode == 0)
	{
		mlx->points[y][x - 1]->x = mlx->start_x - y * dev->y_step + x * dev->x_step;
		mlx->points[y][x - 1]->y = mlx->start_y + y * dev->x_step * mlx->elevation
			+ x * mlx->elevation * dev->y_step - mlx->mesh[y][x] * mlx->unit / mlx->height_factor;
	}
	else
	{
		mlx->points[y][x - 1]->x = mlx->start_x - y * dev->y_step + x * dev->y_step;
		mlx->points[y][x - 1]->y = mlx->start_y + y * dev->x_step
			+ x * dev->x_step - mlx->mesh[y][x] * mlx->unit / mlx->height_factor;
	}
}

char		conditions_continue_y(t_mlx *mlx, t_vector *dev, int y)
{
	//if ((y > 0 && mlx->points[y - 1][0]->y <= 0.0 && dev->y_step < 0.0)
	//	|| (y > 0 && mlx->points[y - 1][0]->y >= HEIGHT && dev->y_step > 0.0))
	//	return (0);
	(void)mlx;
	(void)dev;
	(void)y;
	return (1);
}

char		conditions_continue_x(t_mlx *mlx, t_vector *dev, int x)
{
	(void)mlx;
	(void)dev;
	(void)x;
	return (1);
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

void		set_start_point(t_mlx *mlx, t_vector *dev, int nb_lines)
{
	double		extreme_y;
	double		extreme_x;

	mlx->start_x = 0.0;
	mlx->start_y = 0.0;
	get_coords_at_xy(mlx, nb_lines, mlx->mesh[nb_lines][0], dev);
	get_coords_at_xy(mlx, nb_lines, 1, dev);
	get_coords_at_xy(mlx, 0, 1, dev);
	get_coords_at_xy(mlx, 0, mlx->mesh[0][0], dev);
	extreme_x = get_extreme_x(mlx, nb_lines);
	extreme_y = get_extreme_y(mlx, nb_lines);
	printf("%f, %f\n", extreme_x, extreme_y);
	mlx->start_x = mlx->center->x - extreme_x;
	mlx->start_y = mlx->center->y - extreme_y;
}

void		mesh_to_points(t_mlx *mlx)
{
	int		y;
	int		x;
	int		nb_lines;
	t_vector	*dev;

	//mlx->unit *= 1.1;
	//mlx->height_factor *= 0.9;
	//mlx->view_mode = 1;
	//mlx->color_function = ft_get_color2;
	//mlx->center->x -= 100.0;
	//mlx->center->y -= 10.0;
	//mlx->elevation = 1.00;
	//mlx->angle += 4.0;
	if (mlx->view_mode != 1)
		dev = ft_new_vector(sin(mlx->angle * RAD) * mlx->unit, cos(mlx->angle * RAD) * mlx->unit);
	else
		dev = ft_new_vector(sin(30 * RAD) * mlx->unit, cos(30 * RAD) * mlx->unit);
	nb_lines = ft_nb_lines(mlx->mesh);
	set_start_point(mlx, dev, nb_lines - 1);
	y = 0;
	while (y < nb_lines && conditions_continue_y(mlx, dev, y))
	{
		x = 1;
		while (x <= mlx->mesh[y][0] && conditions_continue_x(mlx, dev, x))
		{
			get_coords_at_xy(mlx, y, x, dev);
			x++;
		}
		y++;
	}
}

void		ft_draw_rect(t_mlx *mlx, int y, int x)
{
	t_rect	*rect;

	if ((rect = ft_new_rect(mlx->points[y][x], mlx->points[y][x + 1]
							, mlx->points[y + 1][x], mlx->points[y + 1][x + 1])))
	{
		draw_full_rect(mlx, rect);
		free(rect);
		rect = NULL;
	}
}

int			ft_render(void *mlx_param)
{
	static int	i = 0;
	t_mlx	*mlx;
	int		x;
	int		y;

	ft_putnbr(i);
	ft_putchar('\n');
	i++;
	mlx = (t_mlx*)mlx_param;
	restore_window(mlx);
	mesh_to_points(mlx);
	y = 0;
	while (mlx->points[y + 1])
	{
		x = 0;
		while (mlx->points[y][x + 1])
		{
			if (!mlx->full_drawing)
			{
				ft_draw_line(mlx, mlx->points[y][x], mlx->points[y][x + 1], mlx->color_function);
				ft_draw_line(mlx, mlx->points[y][x], mlx->points[y + 1][x], mlx->color_function);
				ft_draw_line(mlx, mlx->points[y][x + 1], mlx->points[y + 1][x + 1], mlx->color_function);
				ft_draw_line(mlx, mlx->points[y + 1][x], mlx->points[y + 1][x + 1], mlx->color_function);
			}
			else
				ft_draw_rect(mlx, y, x);
			x++;
		}
		y++;
	}
	ft_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}
