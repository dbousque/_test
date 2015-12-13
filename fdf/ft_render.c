

#include "fdf.h"

int			ft_nb_lines(int **mesh)
{
	int		i;

	i = 0;
	while (mesh[i])
		i++;
	return (i);
}

void		ft_rem_img_from_window(void *mlx, void *win, void *img, int x, int y)
{
	int		*image;

	image = (int*)img;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (image[y * WIDTH + x])
				mlx_pixel_put(mlx, win, x, y, 0);
			x++;
		}
		y++;
	}
}

void		ft_put_image_to_window(void *mlx, void *win, void *img, int x, int y)
{
	int		*image;

	image = (int*)img;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (image[y * WIDTH + x])
				mlx_pixel_put(mlx, win, x, y, image[y * WIDTH + x]);
			x++;
		}
		y++;
	}
}

void		restore_window(t_mlx *mlx)
{
	ft_rem_img_from_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	ft_bzero(mlx->img, mlx->width * mlx->height * sizeof(int));
}

void		get_coords_at_xy(t_mlx *mlx, int y, int x, t_vector *dev)
{
	mlx->points[y][x - 1]->height = mlx->mesh[y][x];
	//mlx->points[y][x - 1]->x = mlx->start_x - y * dev->y_step + x * dev->x_step;
	//mlx->points[y][x - 1]->y = mlx->start_y + y * dev->x_step * 0.52 + x * 0.52 * dev->y_step - mlx->mesh[y][x] * mlx->unit / mlx->height_factor;
	mlx->points[y][x - 1]->x = mlx->start_x - y * dev->y_step + x * dev->y_step;
	mlx->points[y][x - 1]->y = mlx->start_y + y * dev->x_step
		+ x * dev->x_step - mlx->mesh[y][x] * mlx->unit / mlx->height_factor;
	//mlx->points[y][x - 1]->x = mlx->start_x - y * mlx->unit * cos(mlx->angle * RAD) + x * mlx->unit * cos(mlx->angle * RAD);
	//mlx->points[y][x - 1]->y = mlx->start_y + y * mlx->unit * sin(mlx->angle * RAD) + x * mlx->unit * sin(mlx->angle * RAD) - mlx->mesh[y][x] * mlx->unit / mlx->height_factor;
}

void		mesh_to_points(t_mlx *mlx)
{
	int		y;
	int		x;
	int		nb_lines;
	t_vector	*dev;

	mlx->start_x = 400;
	mlx->start_y = 100;
	mlx->unit = 4.0;
	mlx->height_factor = 10.0;
	//mlx->angle += 0.1;
	dev = ft_new_vector(sin(mlx->angle * RAD) * mlx->unit, cos(mlx->angle * RAD) * mlx->unit);
	nb_lines = ft_nb_lines(mlx->mesh);
	y = 0;
	while (y < nb_lines)
	{
		x = 1;
		while (x <= mlx->mesh[y][0])
		{
			get_coords_at_xy(mlx, y, x, dev);
			x++;
		}
		y++;
	}
}

int			ft_render(void *mlx_param)
{
	static int	i = 0;
	t_mlx	*mlx;
	int		x;
	int		y;

	ft_putnbr(i);
	ft_putchar('\n');
	i++;
	mlx = (t_mlx*)mlx_param;
	restore_window(mlx);
	mesh_to_points(mlx);
	y = 0;
	while (mlx->points[y + 1])
	{
		x = 0;
		while (mlx->points[y][x + 1])
		{
			ft_draw_line(mlx, mlx->points[y][x], mlx->points[y][x + 1], mlx->color_function);
			ft_draw_line(mlx, mlx->points[y][x], mlx->points[y + 1][x], mlx->color_function);
			ft_draw_line(mlx, mlx->points[y][x + 1], mlx->points[y + 1][x + 1], mlx->color_function);
			ft_draw_line(mlx, mlx->points[y + 1][x], mlx->points[y + 1][x + 1], mlx->color_function);
			x++;
		}
		y++;
	}
	ft_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}

/*int		ft_render(void *mlx_param)
{
	t_mlx	*mlx;
	int		base;
	double	start_x;
	double	start_y;
	int		x;
	int		y;
	double	current_x;
	double	current_y;
	int		nb_lines;
	//double	decal;

	mlx = (t_mlx*)mlx_param;
	restore_window(mlx);
	nb_lines = ft_nb_lines(mlx->mesh);
	base = 155;
	start_x = 600;
	start_y = 100;
	y = 0;
	while (y < nb_lines - 1)
	{
		x = 1;
		current_x = start_x - y * base * cos(30 * RAD);
		current_y = start_y + y * base * sin(30 * RAD);
		while (x < mlx->mesh[y][0])
		{
			ft_draw_line(mlx, ft_new_point(current_x, current_y, mlx->mesh[y][x]),
						ft_new_point(current_x + base * cos(30 * RAD), current_y + base * sin(30 * RAD), mlx->mesh[y][x + 1]),
							ft_get_color);
			ft_draw_line(mlx, ft_new_point(current_x - base * cos(30 * RAD), current_y + base * sin(30 * RAD), mlx->mesh[y + 1][x]),
						ft_new_point(current_x, current_y, mlx->mesh[y][x]),
							ft_get_color);
			ft_draw_line(mlx, ft_new_point(current_x - base * cos(30 * RAD), current_y + base * sin(30 * RAD), mlx->mesh[y + 1][x]),
						ft_new_point(current_x, current_y + base, mlx->mesh[y + 1][x + 1]),
							ft_get_color);
			ft_draw_line(mlx, ft_new_point(current_x, current_y + base, mlx->mesh[y + 1][x + 1]),
						ft_new_point(current_x + base * cos(30 * RAD), current_y + base * sin(30 * RAD), mlx->mesh[y][x + 1]),
							ft_get_color);
			current_x = start_x - y * base * cos(30 * RAD) + x * base * cos(30 * RAD);
			current_y = start_y + y * base * sin(30 * RAD) + x * base * sin(30 * RAD);
			//current_y -= mlx->mesh[y][x + 1] * base / 15.0;
			x++;
		}
		y++;
	}
	ft_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}*/
