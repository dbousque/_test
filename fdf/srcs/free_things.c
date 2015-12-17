/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 17:30:26 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/17 17:30:40 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_mesh(int **mesh)
{
	int		x;

	x = 0;
	while (mesh[x])
	{
		free(mesh[x]);
		x++;
	}
	free(mesh);
}

void	free_points(t_point ***points)
{
	int		x;
	int		y;

	y = 0;
	while (points[y])
	{
		x = 0;
		while (points[y][x])
		{
			free(points[y][x]);
			x++;
		}
		free(points[y]);
		y++;
	}
	free(points);
}

int		ft_exit(t_mlx *mlx)
{
	free_mesh(mlx->mesh);
	free_points(mlx->points);
	mlx_destroy_image(mlx->mlx, mlx->img);
	free(mlx->center);
	exit(0);
	return (0);
}
