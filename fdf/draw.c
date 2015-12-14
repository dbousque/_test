

#include "fdf.h"

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
		if (x <= WIDTH && y <= HEIGHT)
			img_pixel_put(mlx, lround(x), lround(y),
				ft_clr(mlx, p1, p2, ft_perc(p1, p2, x, y)));
		y += y_step;
		x += x_step;
	}
}

void	draw_full_rect(t_mlx *mlx, t_rect *rect)
{
	//t_point		*tmp1;
	//t_point		*tmp2;

	//tmp1 = ft_new_point((rect->points[0]->x + rect->points[1]->x) / 2.0
	//ft_draw_full_triangle(mlx, re
	ft_draw_line(mlx, rect->points[0], rect->points[1], mlx->color_function);
	ft_draw_line(mlx, rect->points[1], rect->points[3], mlx->color_function);
	ft_draw_line(mlx, rect->points[3], rect->points[2], mlx->color_function);
	ft_draw_line(mlx, rect->points[2], rect->points[0], mlx->color_function);
}
