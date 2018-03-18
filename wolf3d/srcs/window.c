

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
	if (window->antialiasing)
	{
		width *= 2;
		height *= 2;
	}
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

int		pixels_average(int pix1, int pix2, int pix3, int pix4)
{
	int		r;
	int		g;
	int		b;

	r = *(((unsigned char*)&pix1) + 2) + *(((unsigned char*)&pix2) + 2) +
		*(((unsigned char*)&pix3) + 2) + *(((unsigned char*)&pix4) + 2);
	g = *(((unsigned char*)&pix1) + 1) + *(((unsigned char*)&pix2) + 1) +
		*(((unsigned char*)&pix3) + 1) + *(((unsigned char*)&pix4) + 1);
	b = *(((unsigned char*)&pix1) + 0) + *(((unsigned char*)&pix2) + 0) +
		*(((unsigned char*)&pix3) + 0) + *(((unsigned char*)&pix4) + 0);
	r = (int)(((float)r) / 4.0);
	g = (int)(((float)g) / 4.0);
	b = (int)(((float)b) / 4.0);
	return (r * 256 * 256 + g * 256 + b);
}

void	cpy_pixels_to_img_aa(t_window *window)
{
	int		x;
	int		y;
	int		ind;

	y = 0;
	while (y < window->height / 2)
	{
		x = 0;
		while (x < window->width / 2)
		{
			ind = y * (window->width / 2) + x;
			//printf("%d %d %d\n", x, y, ind);
			window->img_pixels[ind] = pixels_average(
				PIXEL_AT(*window, x * 2, y * 2),
				PIXEL_AT(*window, x * 2 + 1, y * 2),
				PIXEL_AT(*window, x * 2, y * 2 + 1),
				PIXEL_AT(*window, x * 2 + 1, y * 2 + 1)
			);
			x++;
		}
		y++;
	}
}

void	cpy_pixels_to_img(t_window *window)
{
	int		x;
	int		y;
	int		ind;

	if (window->antialiasing)
		return (cpy_pixels_to_img_aa(window));
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
