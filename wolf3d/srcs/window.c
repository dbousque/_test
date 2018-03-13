

#include "wolf3d.h"

void	apply_image_to_window(t_window *window)
{
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}

void	clear_window(t_window *window)
{
	mlx_clear_window(window->mlx, window->win);
}

char	init_window(t_window *window, int width, int height, char *title)
{
	int		i;

	if (!(window->mlx = mlx_init()))
		return (0);
	if (!(window->win = mlx_new_window(window->mlx, width, height, title)))
		return (0);
	if (!(window->img = mlx_new_image(window->mlx, width, height)))
		return (0);
	if (!(window->img_pixels = (int*)mlx_get_data_addr(window->img, &i, &i, &i)))
		return (0);
	if (!(window->pixels = malloc(sizeof(int) * (width * height))))
		return (0);
	window->width = width;
	window->height = height;
	window->mouse.x = width / 2;
	window->mouse.y = height / 2;
	i = 0;
	while (i < NB_KEY_PRESS)
	{
		window->pressed_keys[i] = 0;
		i++;
	}
	return (1);
}

void	cpy_pixels_to_img(t_window *window)
{
	int		x;
	int		y;
	int		ind;

	y = 0;
	while (y < window->height)
	{
		x = 0;
		while (x < window->width)
		{
			ind = y * window->width + x;
			window->img_pixels[ind] = window->pixels[ind];
			x++;
		}
		y++;
	}
}
