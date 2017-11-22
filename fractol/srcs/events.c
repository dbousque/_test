

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
	if (new_fractal_ind >= NB_PALETTES)
		new_fractal_ind = 0;
	fractol->current_fractal = new_fractal_ind;
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
	if (IS_P(keycode))
		increment_palette(fractol);
	if (IS_F(keycode))
		increment_fractal(fractol);
	if (IS_B(keycode))
		fractol->big_mode = fractol->big_mode ? 0 : 1;
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