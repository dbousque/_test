

#include "fdf.h"






#include <stdio.h>


void	img_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (y >= 0 && x >= 0 && y * WIDTH + x < mlx->last_pixel)
		mlx->img[y * WIDTH + x] = color;
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

void	ft_draw_line(t_mlx *mlx, t_point *p1, t_point *p2,
			int (*ft_clr) (t_mlx *mlx, t_point *p1, t_point *p2, double perc))
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
		if (x <= WIDTH && y <= HEIGHT && x >= 0.0 && y  >= 0.0)
			img_pixel_put(mlx, lround(x), lround(y),
				ft_clr(mlx, p1, p2, ft_perc(p1, p2, x, y)));
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
		ft_draw_line(mlx, start, end, mlx->color_function);
		start->y += (p1->y > p2->y ? -1 : 1);
		start->x += (p1->y > p2->y ? -x_step1 : x_step1);
		end->y += (p1->y > p2->y ? -1 : 1);
		end->x += (p1->y > p2->y ? -x_step2 : x_step2);
		start->height = (p2->height - p1->height) * ((start->y - p1->y) / (p2->y - p1->y));
		end->height = (p2->height - p3->height) * ((start->y - p3->y) / (p2->y - p3->y));
		printf("%f\n", start->x);
	}
	free(start);
	free(end);
	start = NULL;
	end = NULL;
}

void	sort_points(t_rect *rect, t_point *highest[4])
{
	t_point	*tmp;
	int		i;

	i = 0;
	/*highest[0] = rect->points[1];
	highest[1] = rect->points[0];
	highest[2] = rect->points[3];
	highest[3] = rect->points[2];*/
	
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
			i-=2;
		}
		i++;
	}
}

void	draw_full_rect(t_mlx *mlx, t_rect *rect)
{
	//t_point		*tmp1;
	//t_point		*tmp2;
	t_point		*highest[4];

	sort_points(rect, highest);
	/*tmp1 = ft_new_point((highest[0]->x - highest[2]->x) * ((highest[2]->y - highest[1]->y) / (highest[2]->y - highest[0]->y)) + highest[2]->x
				, highest[1]->y
				, highest[0]->height);
	
	tmp2 = ft_new_point((highest[1]->x - highest[3]->x) * ((highest[3]->y - highest[2]->y) / (highest[3]->y - highest[1]->y)) + highest[3]->x
				, highest[2]->y
				, highest[3]->height);

	ft_draw_full_triangle(mlx, tmp1, highest[0], highest[1]);
	ft_draw_full_triangle(mlx, tmp1, highest[2], highest[1]);

	ft_draw_full_triangle(mlx, highest[2], highest[1], tmp2);
	ft_draw_full_triangle(mlx, highest[2], highest[3], tmp2);
	ft_draw_line(mlx, highest[2], tmp2, ft_get_color3);
	ft_draw_line(mlx, highest[1], tmp1, ft_get_color);*/
	//ft_draw_full_triangle(mlx, highest[1], highest[0], highest[2]);
	//ft_draw_full_triangle(mlx, highest[1], highest[3], highest[2]);
	ft_draw_line(mlx, rect->points[0], rect->points[1], mlx->color_function);
	ft_draw_line(mlx, rect->points[1], rect->points[3], mlx->color_function);
	ft_draw_line(mlx, rect->points[3], rect->points[2], mlx->color_function);
	ft_draw_line(mlx, rect->points[2], rect->points[0], mlx->color_function);
}
