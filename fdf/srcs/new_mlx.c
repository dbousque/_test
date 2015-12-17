/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 21:05:45 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/17 17:35:32 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector	*ft_new_vector(double x, double y)
{
	t_vector	*res;

	if (!(res = (t_vector*)malloc(sizeof(t_vector))))
		return (NULL);
	res->x_step = x;
	res->y_step = y;
	return (res);
}

int			*ft_new_img(int width, int height)
{
	int		*img;

	if (!(img = (int*)malloc(sizeof(int) * width * height)))
		return (NULL);
	return (img);
}

t_point		*ft_create_point_n_update_max(t_mlx *mlx, int y, int x)
{
	t_point		*res;

	if (!(res = ft_new_point(0.0, 0.0, 0.0)))
		return (NULL);
	if (mlx->mesh[y][x] < mlx->lower_point)
		mlx->lower_point = mlx->mesh[y][x];
	else if (mlx->mesh[y][x] > mlx->higher_point)
		mlx->higher_point = mlx->mesh[y][x];
	return (res);
}

t_point		***empty_points(t_mlx *mlx)
{
	int		y;
	int		x;
	int		nb_lines;
	t_point	***res;

	nb_lines = ft_nb_lines(mlx->mesh);
	if (!(res = (t_point***)malloc(sizeof(t_point**) * (nb_lines + 1))))
		return (NULL);
	res[nb_lines] = NULL;
	y = -1;
	while (++y < nb_lines)
	{
		if (!(res[y] = (t_point**)malloc(sizeof(t_point*)
						* (mlx->mesh[y][0] + 1))))
			return (NULL);
		res[y][mlx->mesh[y][0]] = NULL;
		x = 1;
		while (x <= mlx->mesh[y][0])
		{
			if (!(res[y][x - 1] = ft_create_point_n_update_max(mlx, y, x)))
				return (NULL);
			x++;
		}
	}
	return (res);
}

t_mlx		*ft_new_mlx(int width, int height, char *title)
{
	t_mlx	*res;

	if (!(res = (t_mlx*)malloc(sizeof(t_mlx))))
		return (NULL);
	if (!(res->mlx = mlx_init()))
		return (NULL);
	if (!(res->win = mlx_new_window(res->mlx, width, height, title)))
		return (NULL);
	if (!(res->img = ft_new_img(width, height)))
		return (NULL);
	res->last_pixel = width * height;
	res->width = width;
	res->height = height;
	res->unit = 4.0;
	res->height_factor = 10.0;
	res->angle = 30.0;
	res->clr_fct = ft_get_color;
	res->clr_function_num = 0;
	res->view_mode = 0;
	res->elevation = 0.72;
	res->center = ft_new_point(WIDTH / 2, HEIGHT / 2, 0.0);
	return (res);
}
