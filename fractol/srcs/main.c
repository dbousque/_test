/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:32:17 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 14:32:18 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	maybe_update_fractal_params(t_fractol *fractol)
{
	t_fractal	*fractal;

	fractal = &(fractol->fractals[fractol->current_fractal]);
	if (fractal->update_mouse_params)
	{
		fractal->params[1] = fractol->window.mouse.x;
		fractal->params[2] = fractol->window.mouse.y;
	}
}

void	update_values_with_input(t_fractol *fractol)
{
	float		delta;
	t_fractal	*fractal;

	fractal = &(fractol->fractals[fractol->current_fractal]);
	delta = millis_since(&(fractol->last_frame));
	delta /= 30.0;
	if (fractol->window.pressed_keys[0])
		fractal->decal_y -= (20.0 * delta) / fractal->zoom;
	if (fractol->window.pressed_keys[1])
		fractal->decal_x -= (20.0 * delta) / fractal->zoom;
	if (fractol->window.pressed_keys[2])
		fractal->decal_y += (20.0 * delta) / fractal->zoom;
	if (fractol->window.pressed_keys[3])
		fractal->decal_x += (20.0 * delta) / fractal->zoom;
	if (fractol->window.pressed_keys[4])
		fractal->params[0] *= (1.0 + (delta / 20));
	if (fractol->window.pressed_keys[5])
		fractal->params[0] *= (1.0 - (delta / 20));
	if (fractol->window.pressed_keys[6])
		zoom_on_mouse(fractal, 1.05, fractol);
	if (fractol->window.pressed_keys[7])
		zoom_on_mouse(fractal, 0.95, fractol);
}

void	init_loop(int *i, char *key_pressed)
{
	*key_pressed = 0;
	*i = 0;
}

int		loop(void *param)
{
	t_fractol	*fractol;
	int			i;
	char		key_pressed;

	fractol = (t_fractol*)param;
	init_loop(&i, &key_pressed);
	while (i < NB_KEY_PRESS)
	{
		if (fractol->window.pressed_keys[i])
			key_pressed = 1;
		i++;
	}
	if (!fractol->changed && !key_pressed)
	{
		gettimeofday(&(fractol->last_frame), NULL);
		return (0);
	}
	fractol->changed = 0;
	if (key_pressed)
		update_values_with_input(fractol);
	maybe_update_fractal_params(fractol);
	gettimeofday(&(fractol->last_frame), NULL);
	compute_fractol(fractol);
	render_fractol(fractol);
	return (0);
}

int		main(int argc, char **argv)
{
	t_fractol	fractol;
	int			width;
	int			height;

	if (!(parse_opts(argc, argv, &width, &height)))
		return (0);
	if (!init_fractol(&fractol, width, height, "fractol - dbousque"))
		return (1);
	maybe_update_current_fractal(&fractol, argc, argv);
	mlx_loop_hook(fractol.window.mlx, loop, (void*)&fractol);
	mlx_loop(fractol.window.mlx);
	return (0);
}
