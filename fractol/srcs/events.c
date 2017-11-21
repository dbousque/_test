

#include "fractol.h"

int		expose_hook(void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol*)param;
	fractol->changed = 1;
	return (0);
}

int		key_hook(int keycode, void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol*)param;
	fractol->changed = 1;
	if (IS_ESC(keycode))
		return (exit_fractol(fractol));
	if (IS_X(keycode))
		fractol->fractals[fractol->current_fractal].params[0] *= 1.05;
	if (IS_Z(keycode))
		fractol->fractals[fractol->current_fractal].params[0] /= 1.05;
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