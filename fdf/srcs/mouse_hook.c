/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 17:33:23 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/17 17:37:09 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	make_point_higher(t_mlx *mlx, int ind_y, int ind_x)
{
	if (mlx->higher_point - mlx->lower_point < 10)
	{
		mlx->mesh[ind_y][ind_x + 1] = mlx->mesh[ind_y][ind_x + 1] + 1;
		mlx->higher_point += 1;
	}
	else
		mlx->mesh[ind_y][ind_x + 1] += (mlx->higher_point
												- mlx->lower_point) / 10;
	if (mlx->mesh[ind_y][ind_x + 1] > mlx->higher_point)
		mlx->higher_point = mlx->mesh[ind_y][ind_x + 1];
}

void	update_point(t_mlx *mlx, int ind_y, int ind_x, int keycode)
{
	if (keycode == 1)
		make_point_higher(mlx, ind_y, ind_x);
	else
	{
		if (mlx->higher_point - mlx->lower_point < 10)
		{
			mlx->mesh[ind_y][ind_x + 1] = mlx->mesh[ind_y][ind_x + 1] - 1;
			mlx->lower_point -= 1;
		}
		else
			mlx->mesh[ind_y][ind_x + 1] -= (mlx->higher_point
												- mlx->lower_point) / 10;
		if (mlx->mesh[ind_y][ind_x + 1] < mlx->lower_point)
			mlx->lower_point = mlx->mesh[ind_y][ind_x + 1];
	}
	ft_render(mlx);
}

int		mouse_hook(int keycode, int x, int y, t_mlx *mlx)
{
	int		i[2];
	double	score;
	int		ind[2];

	score = -1.0;
	i[0] = 0;
	while (mlx->points[i[0]])
	{
		i[1] = 0;
		while (mlx->points[i[0]][i[1]])
		{
			if (score == -1.0 || ft_real_value(mlx->points[i[0]][i[1]]->x - x)
					+ ft_real_value(mlx->points[i[0]][i[1]]->y - y) < score)
			{
				score = ft_real_value(mlx->points[i[0]][i[1]]->x - x)
					+ ft_real_value(mlx->points[i[0]][i[1]]->y - y);
				ind[0] = i[0];
				ind[1] = i[1];
			}
			i[1]++;
		}
		i[0]++;
	}
	update_point(mlx, ind[0], ind[1], keycode);
	return (0);
}
