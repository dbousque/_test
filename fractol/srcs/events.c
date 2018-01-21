

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

int		key_pressed_hook2(int keycode, t_fractol *fractol, t_fractal *fractal)
{
	if (IS_PLUS_BIS(keycode))
		fractal->max_iter++;
	if (IS_MINUS_BIS(keycode))
	{
		fractal->max_iter--;
		fractal->max_iter = fractal->max_iter < 2 ? 2 : fractal->max_iter;
	}
	if (IS_UP(keycode))
		fractol->window.pressed_keys[0] = 1;
	if (IS_LEFT(keycode))
		fractol->window.pressed_keys[1] = 1;
	if (IS_DOWN(keycode))
		fractol->window.pressed_keys[2] = 1;
	if (IS_RIGHT(keycode))
		fractol->window.pressed_keys[3] = 1;
	if (IS_M(keycode))
		fractal->update_mouse_params = fractal->update_mouse_params ? 0 : 1;
	fractol->changed = 1;
	return (0);
}

int		key_pressed_hook(int keycode, void *param)
{
	t_fractol	*fractol;
	t_fractal	*fractal;

	fractol = (t_fractol*)param;
	fractal = &(fractol->fractals[fractol->current_fractal]);
	if (IS_ESC(keycode))
		return (exit_fractol(fractol));
	if (IS_X(keycode))
		fractol->window.pressed_keys[4] = 1;
	if (IS_Z(keycode))
		fractol->window.pressed_keys[5] = 1;
	if (IS_P(keycode))
		increment_palette(fractol);
	if (IS_F(keycode))
		increment_fractal(fractol);
	if (IS_B(keycode))
		fractol->big_mode = fractol->big_mode ? 0 : 1;
	if (IS_PLUS(keycode))
		fractol->window.pressed_keys[6] = 1;
	if (IS_MINUS(keycode))
		fractol->window.pressed_keys[7] = 1;
	return (key_pressed_hook2(keycode, fractol, fractal));
}

int		key_released_hook(int keycode, void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol*)param;
	if (IS_X(keycode))
		fractol->window.pressed_keys[4] = 0;
	if (IS_Z(keycode))
		fractol->window.pressed_keys[5] = 0;
	if (IS_PLUS(keycode))
		fractol->window.pressed_keys[6] = 0;
	if (IS_MINUS(keycode))
		fractol->window.pressed_keys[7] = 0;
	if (IS_UP(keycode))
		fractol->window.pressed_keys[0] = 0;
	if (IS_LEFT(keycode))
		fractol->window.pressed_keys[1] = 0;
	if (IS_DOWN(keycode))
		fractol->window.pressed_keys[2] = 0;
	if (IS_RIGHT(keycode))
		fractol->window.pressed_keys[3] = 0;
	return (0);
}

int		mouse_move_hook(int x, int y, void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol*)param;
	fractol->changed = 1;
	fractol->window.mouse.x = x;
	fractol->window.mouse.y = y;
	return (0);
}

int		mouse_hook(int keycode, int x, int y, void *param)
{
	t_fractol	*fractol;
	t_fractal	*fractal;

	fractol = (t_fractol*)param;
	fractal = &(fractol->fractals[fractol->current_fractal]);
	fractol->changed = 1;
	fractol->window.mouse.x = x;
	fractol->window.mouse.y = y;
	if (IS_MOUSE_FORWARD(keycode))
		zoom_on_mouse(fractal, 1.05, fractol);
	if (IS_MOUSE_BACKWARDS(keycode))
		zoom_on_mouse(fractal, 0.95, fractol);
	return (0);
}