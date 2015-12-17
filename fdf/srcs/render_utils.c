/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 17:40:50 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/17 17:42:31 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			ft_nb_lines(int **mesh)
{
	int		i;

	i = 0;
	while (mesh[i])
		i++;
	return (i);
}

void		ft_put_image_to_window(void *mlx, void *win, void *img)
{
	mlx_put_image_to_window(mlx, win, img, 0, 0);
}

void		restore_window(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->pixels = mlx_get_data_addr(mlx->img, &(mlx->bpp), &(mlx->s_line)
					, &(mlx->ed));
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
	mlx->start_x = mlx->center->x - extreme_x;
	mlx->start_y = mlx->center->y - extreme_y;
}
