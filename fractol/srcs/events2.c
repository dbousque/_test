/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:35:20 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 14:35:21 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
