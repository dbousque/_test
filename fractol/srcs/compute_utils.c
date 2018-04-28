/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:49:53 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 14:49:55 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		millis_since(struct timeval *start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return (1000 * (end.tv_sec - start->tv_sec)
		+ (end.tv_usec - start->tv_usec) / 1000);
}

void	print_time_taken(struct timeval *start, char *before, char *after)
{
	char			ms[30];
	int				time_taken;

	ft_putstr(before);
	time_taken = millis_since(start);
	ft_itoa(time_taken, ms);
	ft_putstr(ms);
	ft_putstr(" ms");
	ft_putstr(after);
}

void	render_fractol(t_fractol *fractol)
{
	apply_image_to_window(&(fractol->window));
}

char	init_fractol(t_fractol *fractol, int width, int height, char *title)
{
	fractol->changed = 1;
	fractol->current_fractal = 0;
	init_fractals(fractol);
	gettimeofday(&(fractol->last_frame), NULL);
	fractol->current_palette = 0;
	fractol->big_mode = 0;
	init_palettes(fractol->palettes);
	if (!(init_window(&(fractol->window), width, height, title)))
	{
		ft_putstr("Could not initialize window\n");
		return (0);
	}
	mlx_expose_hook(fractol->window.win, expose_hook, (void*)fractol);
	mlx_mouse_hook(fractol->window.win, mouse_hook, (void*)fractol);
	mlx_hook(fractol->window.win, 6, 1L << 6, mouse_move_hook, (void*)fractol);
	mlx_hook(fractol->window.win, 2, 1, key_pressed_hook, (void*)fractol);
	mlx_hook(fractol->window.win, 3, 2, key_released_hook, (void*)fractol);
	return (1);
}
