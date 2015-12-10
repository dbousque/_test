


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

int		ft_get_color(t_point *p1, t_point *p2, double percentage)
{
	(void)p1;
	(void)p2;
	(void)percentage;
	return (0xFF0000);
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
			int (*ft_clr) (t_point *p1, t_point *p2, double perc))
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
			&& ((xy_hi[0] && x >= p2->x) || (!xy_hi[0] && x <= p2->x)))
	{
		mlx_pixel_put(mlx->mlx, mlx->win, lround(x), lround(y),
				ft_clr(p1, p2, ft_perc(p1, p2, x, y)));
		y += y_step;
		x += x_step;
	}
}

void	ft_draw_rect(t_mlx *mlx, t_rect *rect,
			int (*ft_clr) (t_point *p1, t_point *p2, double perc))
{
	ft_draw_line(mlx, rect->points[0], rect->points[1], ft_clr);
	ft_draw_line(mlx, rect->points[1], rect->points[2], ft_clr);
	ft_draw_line(mlx, rect->points[2], rect->points[3], ft_clr);
	ft_draw_line(mlx, rect->points[3], rect->points[0], ft_clr);
}

void	ft_draw_full_triangle(t_mlx *mlx, t_point *p1, t_point *p2, t_point *p3)
{
	double	x_step1;
	double	y_step1;
	double	x_step2;
	double	y_step2;
	int		nb_steps[2];



	t_point	*tmp1;
	t_point	*tmp2;
	int		max_steps;

	ft_get_steps(p2, p1, &x_step1, &y_step1);
	ft_get_steps(p2, p3, &x_step2, &y_step2);
	if (ft_real_value(x_step1) > ft_real_value(y_step1))
		nb_steps[0] = (int)(ft_real_value(p1->x - p2->x)) + 1;
	else
		nb_steps[0] = (int)(ft_real_value(p1->y - p2->y)) + 1;
	if (ft_real_value(x_step2) > ft_real_value(y_step2))
		nb_steps[1] = (int)(ft_real_value(p3->x - p2->x)) + 1;
	else
		nb_steps[1] = (int)(ft_real_value(p3->y - p2->y)) + 1;
	if (nb_steps[0] > nb_steps[1])
	{
		x_step2 /= (((double)(nb_steps[0])) / nb_steps[1]);
		y_step2 /= (((double)(nb_steps[0])) / nb_steps[1]);
		max_steps = nb_steps[0];
	}
	else
	{
		x_step1 /= (((double)(nb_steps[1])) / nb_steps[0]);
		y_step1 /= (((double)(nb_steps[1])) / nb_steps[0]);
		max_steps = nb_steps[1];
	}
	tmp1 = ft_new_point(p2->x, p2->y, p2->height);
	tmp2 = ft_new_point(p2->x, p2->y, p2->height);
	ft_draw_line(mlx, p1, p2, ft_get_color);
	ft_draw_line(mlx, p2, p3, ft_get_color);
	ft_draw_line(mlx, p1, p3, ft_get_color);
	while (max_steps >= 0)
	{
		ft_draw_line(mlx, tmp1, tmp2, ft_get_color);
		tmp1->x += x_step1;
		tmp1->y += y_step1;
		tmp2->x += x_step2;
		tmp2->y += y_step2;
		max_steps--;
	}
}

void	ft_draw_full_rect(t_mlx *mlx, t_rect *rect,
			int (*ft_clr) (t_point *p1, t_point *p2, double perc))
{
	(void)ft_clr;
	ft_draw_full_triangle(mlx, rect->points[0], rect->points[1], rect->points[2]);
	ft_draw_full_triangle(mlx, rect->points[0], rect->points[3], rect->points[2]);
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

t_mlx	*ft_new_mlx(int width, int height, char *title)
{
	t_mlx	*res;

	if (!(res = (t_mlx*)malloc(sizeof(t_mlx))))
		return (NULL);
	if (!(res->mlx = mlx_init()))
		return (NULL);
	if (!(res->win = mlx_new_window(res->mlx, width, height, title)))
		return (NULL);
	if (!(res->img = mlx_new_image(res->mlx, width, height)))
		return (NULL);
	res->width = width;
	res->height = height;
	return (res);
}

void	ft_putintint(int **mesh)
{
	int		i;
	int		x;

	i = 0;
	while (mesh[i])
	{
		x = 0;
		while (x <= mesh[i][0])
		{
			ft_putnbr(mesh[i][x]);
			ft_putchar('.');
			x++;
		}
		ft_putchar('\n');
		i++;
	}
}

t_pov	*ft_stdpov(void)
{
	t_pov	*res;

	if (!(res = (t_pov*)malloc(sizeof(t_pov))))
		return (NULL);
	res->x = (double)(WIDTH / 2);
	res->y = (double)(HEIGHT / 2);
	res->height = 500.0;
	res->head_balance = 0.0;
	return (res);
}

int		ft_unexpected_error(void)
{
	ft_putendl("unexpected error");
	return (1);
}

int		ft_map_error(void)
{
	ft_putendl("map error");
	return (1);
}

int		ft_connection_failed(void)
{
	ft_putendl("connection to X server failed");
	return (1);
}

int		main(int argc, char **argv)
{
	t_mlx	*mlx;
	int		**mesh;
	t_pov	*pov;

	if (argc == 2)
	{
		if (!(mesh = ft_get_mesh(argv[1])))
			return (ft_map_error());
		ft_putintint(mesh);
		if (!(pov = ft_stdpov()))
			return (ft_unexpected_error());
		if (!(mlx = ft_new_mlx(WIDTH, HEIGHT, "fdf")))
			return (ft_connection_failed());
		pov->head_balance = 30.0;
		mlx->mesh = mesh;
		mlx->pov = pov;
		//ft_render_mesh(mlx);
		mlx_loop_hook(mlx->mlx, ft_render_mesh, (void*)mlx);
		mlx_loop(mlx->mlx);
		//sleep(5);
	}
	return (0);
}
