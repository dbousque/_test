/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 17:38:44 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/17 17:41:25 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*ft_new_point(double x, double y, int height)
{
	t_point	*res;

	if (!(res = (t_point*)malloc(sizeof(t_point))))
		return (NULL);
	res->x = x;
	res->y = y;
	res->height = height;
	return (res);
}

t_rect	*ft_new_rect(t_point *one, t_point *two, t_point *three, t_point *four)
{
	t_rect	*res;

	if (!(res = (t_rect*)malloc(sizeof(t_rect))))
		return (NULL);
	if (!(res->points = (t_point**)malloc(sizeof(t_point*) * 4)))
		return (NULL);
	res->points[0] = one;
	res->points[1] = two;
	res->points[2] = three;
	res->points[3] = four;
	return (res);
}

double	ft_real_value(double value)
{
	if (value < 0)
		return (-value);
	return (value);
}

double	ft_perc(t_point *p1, t_point *p2, double x, double y)
{
	double	diff;

	if (p1->x != p2->x)
	{
		diff = ft_real_value(p2->x - p1->x);
		return ((ft_real_value(x - p1->x) * 100) / diff);
	}
	else
	{
		diff = ft_real_value(p2->y - p1->y);
		return ((ft_real_value(y - p1->y) * 100) / diff);
	}
}

void		ft_draw_void_rect(t_mlx *mlx, int y, int x)
{
	ft_draw_line(mlx, mlx->points[y][x], mlx->points[y][x + 1]);
	if (mlx->mesh[y + 1][0] > x)
		ft_draw_line(mlx, mlx->points[y][x], mlx->points[y + 1][x]);
	if (mlx->mesh[y + 1][0] > x + 1)
	{
		ft_draw_line(mlx, mlx->points[y][x + 1], mlx->points[y + 1][x + 1]);
		ft_draw_line(mlx, mlx->points[y + 1][x], mlx->points[y + 1][x + 1]);
	}
}
