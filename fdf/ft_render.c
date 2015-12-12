

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

t_point		*get_coords_at_xy(t_mlx *mlx, int y, int x)
{
	t_point		*res;

	if (!(res = (t_point*)malloc(sizeof(t_point))))
		return (NULL);
	res->height = mlx->mesh[y][x];
	res->x = mlx->start_x - y * mlx->unit * cos(30 * RAD) + x * mlx->unit * cos(30 * RAD);
	res->y = mlx->start_y + y * mlx->unit * sin(30 * RAD) + x * mlx->unit * sin(30 * RAD) - res->height * mlx->unit / mlx->height_factor;
	return (res);
}

t_point		***mesh_to_points(t_mlx *mlx)
{
	int		y;
	int		x;
	int		nb_lines;
	t_point	***res;

	mlx->start_x = 400;
	mlx->start_y = 100;
	mlx->unit = 20.0;
	mlx->height_factor = 5.0;
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
			if (!(res[y][x - 1] = get_coords_at_xy(mlx, y, x)))
				return (NULL);
			x++;
		}
		y++;
	}
	return (res);
}

int			ft_render(void *mlx_param)
{
	t_mlx	*mlx;
	int		x;
	int		y;

	mlx = (t_mlx*)mlx_param;
	restore_window(mlx);
	mlx->points = mesh_to_points(mlx);
	y = 0;
	while (mlx->points[y + 1])
	{
		x = 0;
		while (mlx->points[y][x + 1])
		{
			ft_draw_line(mlx, mlx->points[y][x], mlx->points[y][x + 1], ft_get_color);
			ft_draw_line(mlx, mlx->points[y][x], mlx->points[y + 1][x], ft_get_color);
			ft_draw_line(mlx, mlx->points[y][x + 1], mlx->points[y + 1][x + 1], ft_get_color);
			ft_draw_line(mlx, mlx->points[y + 1][x], mlx->points[y + 1][x + 1], ft_get_color);
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
