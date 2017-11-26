

#include "fractol.h"

int		expose_hook(void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol*)param;
	fractol->changed = 1;
	return (0);
}

void	increment_palette(t_fractol *fractol)
{
	int		new_palette_ind;

	new_palette_ind = fractol->current_palette + 1;
	if (new_palette_ind >= NB_PALETTES)
		new_palette_ind = 0;
	fractol->current_palette = new_palette_ind;
}

void	increment_fractal(t_fractol *fractol)
{
	int		new_fractal_ind;

	new_fractal_ind = fractol->current_fractal + 1;
	if (new_fractal_ind >= NB_FRACTALS)
		new_fractal_ind = 0;
	fractol->current_fractal = new_fractal_ind;
}

void	zoom_on_point(t_fractal *fractal, int x, int y, float quantity, t_fractol *fractol)
{
	(void)x;
	(void)y;
	fractal->zoom *= quantity;
	if (quantity >= 1.0)
	{
		fractal->decal_x += (x / (float)fractol->window.width) * 60 * fractal->zoom;
		fractal->decal_y += (y / (float)fractol->window.height) * 40 * fractal->zoom;
	}
	else
	{
		fractal->decal_x -= (x / (float)fractol->window.width) * 60 * fractal->zoom;
		fractal->decal_y -= (y / (float)fractol->window.height) * 40 * fractal->zoom;
	}
}

#include <stdio.h>
int		key_hook(int keycode, void *param)
{
	t_fractol	*fractol;
	t_fractal	*fractal;

	printf("key : %d\n", keycode);
	fractol = (t_fractol*)param;
	fractal = &(fractol->fractals[fractol->current_fractal]);
	if (IS_ESC(keycode))
		return (exit_fractol(fractol));
	if (IS_X(keycode))
		fractal->params[0] *= 1.05;
	if (IS_Z(keycode))
		fractal->params[0] /= 1.05;
	if (IS_P(keycode))
		increment_palette(fractol);
	if (IS_F(keycode))
		increment_fractal(fractol);
	if (IS_B(keycode))
		fractol->big_mode = fractol->big_mode ? 0 : 1;
	if (IS_PLUS(keycode))
		zoom_on_point(fractal, fractol->window.width / 2, fractol->window.height / 2, 1.05, fractol);
	if (IS_MINUS(keycode))
		zoom_on_point(fractal, fractol->window.width / 2, fractol->window.height / 2, 0.95, fractol);
	if (IS_PLUS_BIS(keycode))
		fractal->max_iter++;
	if (IS_MINUS_BIS(keycode))
		fractal->max_iter--;
	if (IS_W(keycode))
		fractal->decal_y -= 30.0;
	if (IS_A(keycode))
		fractal->decal_x -= 30.0;
	if (IS_S(keycode))
		fractal->decal_y += 30.0;
	if (IS_D(keycode))
		fractal->decal_x += 30.0;
	fractol->changed = 1;
	return (0);
}

int		mouse_hook(int keycode, int x, int y, void *param)
{
	t_fractol	*fractol;

	(void)keycode;
	fractol = (t_fractol*)param;
	fractol->changed = 1;
	fractol->window.mouse.x = x;
	fractol->window.mouse.y = y;
	return (0);
}