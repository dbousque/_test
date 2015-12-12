


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
	double	height;
	int		green;

	if (p1->height || p2->height)
	{
		//ft_putstr("P1 : ");
		//ft_putnbr((int)p1->height);
		//ft_putstr(", P2 : ");
		//ft_putnbr((int)p2->height);
		//ft_putchar('\n');
	}
	height = p1->height + ((p2->height - p1->height) * percentage / 100.0);
	if (height)
	{
		//ft_putnbr((int)height);
		//ft_putchar('\n');
	}
	green = 0x0000CC - height * 10;
	return (0xCC00CC + green * 256);
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

void	img_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (y >= 0 && x >= 0 && y * WIDTH + x < mlx->last_pixel)
		mlx->img[y * WIDTH + x] = color;
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
		img_pixel_put(mlx, lround(x), lround(y),
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

int		*ft_new_img(int width, int height)
{
	int		*img;

	if (!(img = (int*)malloc(sizeof(int) * width * height)))
		return (NULL);
	return (img);
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
	y = 0;
	while (y < nb_lines)
	{
		if (!(res[y] = (t_point**)malloc(sizeof(t_point*) * (mlx->mesh[y][0] + 1))))
			return (NULL);
		res[y][mlx->mesh[y][0]] = NULL;
		x = 1;
		while (x <= mlx->mesh[y][0])
		{
			if (!(res[y][x - 1] = ft_new_point(0.0, 0.0, 0.0)))
				return (NULL);
			x++;
		}
		y++;
	}
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
	if (!(res->img = ft_new_img(width, height)))
		return (NULL);
	res->last_pixel = width * height;
	res->width = width;
	res->height = height;
	res->unit = 130.0;
	res->height_factor = 15.0;
	res->angle = 30.0;
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
	res->zoom = 2.0;
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
		pov->head_balance = 0.0;
		mlx->mesh = mesh;
		mlx->pov = pov;
		if (!(mlx->points = empty_points(mlx)))
			return (ft_unexpected_error());
		//ft_render_mesh(mlx);
		mlx_mouse_hook(mlx->win, ft_get_mouse, mlx);
		mlx_loop_hook(mlx->mlx, ft_render, (void*)mlx);
		mlx_loop(mlx->mlx);
		//sleep(5);
	}
	return (0);
}
