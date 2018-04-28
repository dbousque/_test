/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:31:45 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 14:31:47 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		expose_hook(void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol*)param;
	fractol->changed = 1;
	return (0);
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
