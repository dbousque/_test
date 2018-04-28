/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:32:44 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 14:32:48 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

void	clear_screen(t_fractol *fractol)
{
	int			x;
	int			y;

	x = 0;
	while (x < fractol->window.width)
	{
		y = 0;
		while (y < fractol->window.height)
		{
			set_color_at(fractol, x, y, 0x000000);
			y++;
		}
		x++;
	}
}

void	draw_line(t_fractol *f, double from[2], double to[2], int iter)
{
	double	x;
	double	y;
	double	step_x;
	double	step_y;
	int		co;

	step_x = fabs(to[0] - from[0]);
	step_y = fabs(to[1] - from[1]);
	x = fmax(step_x, step_y);
	step_x /= x;
	step_y /= x;
	x = from[0];
	y = from[1];
	step_x = to[0] < from[0] ? -step_x : step_x;
	step_y = to[1] < from[1] ? -step_y : step_y;
	co = f->palettes[f->current_palette][iter % PALETTE_LEN];
	co = iter == f->fractals[f->current_fractal].max_iter ? 0 : co;
	while (((step_x >= 0.0 && x <= to[0]) || (step_x < 0.0 && x >= to[0]))
		&& ((step_y >= 0.0 && y <= to[1]) || (step_y < 0.0 && y >= to[1])))
	{
		if (x < f->window.width && y < f->window.height && x >= 0 && y >= 0)
			set_color_at(f, (int)x, (int)y, co);
		x += step_x;
		y += step_y;
	}
}
