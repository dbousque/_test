/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 14:35:03 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/17 17:40:20 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	int		i;

	i = x * 4 + y * mlx->s_line;
	if (y >= 0 && x >= 0 && y * WIDTH + x < mlx->last_pixel)
	{
		mlx->pixels[i + 2] = color / (256 * 256);
		mlx->pixels[i + 1] = (color / 256) % 256;
		mlx->pixels[i] = color % (256 * 256);
	}
}

void	ft_get_steps(t_point *p1, t_point *p2, double *x_step, double *y_step)
{
	int		max;

	*x_step = (double)(p2->x - p1->x);
	*y_step = (double)(p2->y - p1->y);
	if (ft_real_value(*x_step) > ft_real_value(*y_step))
		max = *x_step;
	else
		max = *y_step;
	*y_step /= ft_real_value(max);
	*x_step /= ft_real_value(max);
}

void	ft_draw_line(t_mlx *mlx, t_point *p1, t_point *p2)
{
	double	x;
	double	y;
	double	x_step;
	double	y_step;
	char	xy_hi[2];

	ft_get_steps(p1, p2, &x_step, &y_step);
	y = (double)p1->y;
	x = (double)p1->x;
	xy_hi[0] = (p1->x > p2->x ? 1 : 0);
	xy_hi[1] = (p1->y > p2->y ? 1 : 0);
	while (((xy_hi[1] && y >= p2->y) || (!xy_hi[1] && y <= p2->y))
			&& ((xy_hi[0] && x >= p2->x) || (!xy_hi[0] && x <= p2->x))
			&& (x <= WIDTH || x_step < 0.0) && (y <= HEIGHT || y_step < 0.0))
	{
		if (x <= WIDTH && y <= HEIGHT && x >= 0.0 && y >= 0.0)
			img_pixel_put(mlx, lround(x), lround(y),
				mlx->clr_fct(mlx, p1, p2, ft_perc(p1, p2, x, y)));
		y += y_step;
		x += x_step;
	}
}

void	ft_draw_full_triangle(t_mlx *mlx, t_point *p1, t_point *p2, t_point *p3)
{
	t_point		*start;
	t_point		*end;
	double		x_step1;
	double		x_step2;

	start = ft_new_point(p1->x, p1->y, p1->height);
	end = ft_new_point(p3->x, p3->y, p2->height);
	x_step1 = ((int)(p2->x - p1->x)) / (p2->y - p1->y);
	x_step2 = ((int)(p2->x - p3->x)) / (p2->y - p3->y);
	while ((p1->y > p2->y ? start->y >= p2->y : start->y <= p2->y))
	{
		ft_draw_line(mlx, start, end);
		start->y += (p1->y > p2->y ? -1 : 1);
		start->x += (p1->y > p2->y ? -x_step1 : x_step1);
		end->y += (p1->y > p2->y ? -1 : 1);
		end->x += (p1->y > p2->y ? -x_step2 : x_step2);
		start->height = (p2->height - p1->height)
			* ((start->y - p1->y) / (p2->y - p1->y));
		end->height = (p2->height - p3->height)
			* ((start->y - p3->y) / (p2->y - p3->y));
	}
	free(start);
	free(end);
}

void	sort_points(t_rect *rect, t_point *highest[4])
{
	t_point	*tmp;
	int		i;

	i = 0;
	highest[0] = rect->points[2];
	highest[1] = rect->points[3];
	highest[2] = rect->points[0];
	highest[3] = rect->points[1];
	while (i < 4)
	{
		if (i > 0 && highest[i]->y < highest[i - 1]->y)
		{
			tmp = highest[i];
			highest[i] = highest[i - 1];
			highest[i - 1] = tmp;
			i -= 2;
		}
		i++;
	}
}
