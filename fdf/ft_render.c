

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

t_point		**mesh_to_points(int **mesh)
{
	int		y;
	int		x;
	int		nb_lines;
	double	base;
	t_point	***res;

	nb_lines = ft_nb_lines(mesh);
	base = 150.0;
	if (!(res = (t_point***)malloc(sizeof(t_point**) * (nb_lines + 1))))
		return (NULL);
	y = 0;
	while (y < nb_lines)
	{
		if (!(res[y] = (t_point**)malloc(sizeof(t_point*) * (mesh[y][0] + 1))))
			return (NULL);
		x = 1;
		while (x <= mesh[y][0])
		{
			x++;
		}
		y++;
	}
}

int		ft_render(void *mlx_param)
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
	base = 150;
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
			current_y -= mlx->mesh[y][x + 1] * base / 15.0;
			x++;
		}
		y++;
	}
	ft_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}
