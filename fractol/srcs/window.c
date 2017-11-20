

#include "fractol.h"

void	apply_image_to_window(t_window *window)
{
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}

void	clear_window(t_window *window)
{
	mlx_clear_window(window->mlx, window->win);
}

void	render_window(t_window *window)
{
	// clear_window(window);
	PIXEL_AT(window, 100, 100) = 0xFFFFFF;
	PIXEL_AT(window, 101, 100) = 0xFFFFFF;
	PIXEL_AT(window, 100, 101) = 0xFFFFFF;
	PIXEL_AT(window, 101, 101) = 0xFFFFFF;
	PIXEL_AT(window, 99, 100) = 0xFFFFFF;
	PIXEL_AT(window, 100, 99) = 0xFFFFFF;
	apply_image_to_window(window);
}

char	init_window(t_window *window, int width, int height, char *title)
{
	int		z;

	if (!(window->mlx = mlx_init()))
		return (0);
	if (!(window->win = mlx_new_window(window->mlx, width, height, title)))
		return (0);
	if (!(window->img = mlx_new_image(window->mlx, width, height)))
		return (0);
	if (!(window->pixels = (int*)mlx_get_data_addr(window->img, &z, &z, &z)))
		return (0);
	window->width = width;
	mlx_expose_hook(window->win, expose_hook, (void*)window);
	mlx_hook(window->win, 2, 3, key_hook, (void*)window);
	mlx_mouse_hook(window->win, mouse_hook, (void*)window);
	return (1);
}