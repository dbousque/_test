/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:31:54 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 14:31:56 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mandelbrot(t_fractal *fractal, double px, double py, t_window *w)
{
	float		*params;
	double		decals[3];
	double		x;
	double		y;
	int			iteration;

	params = fractal->params;
	decals[0] = px / (w->width / 3.0) - 2.5;
	decals[1] = py / (w->height / 2.0) - 1.0;
	x = 0.0;
	y = 0.0;
	iteration = 0;
	while (x * x + y * y < params[0] && iteration < fractal->max_iter)
	{
		decals[2] = x * x - y * y + decals[0];
		y = 2 * x * y + decals[1];
		x = decals[2];
		iteration++;
	}
	return (iteration);
}

int		julia(t_fractal *fractal, double px, double py, t_window *w)
{
	float		*params;
	double		cs[2];
	double		old[2];
	double		new[2];
	int			iteration;

	params = fractal->params;
	params[0] = 4.0;
	cs[0] = -1.2 + (params[1] / 500.0);
	cs[1] = 0.27 + (params[2] / 1000.0);
	new[0] = px / (w->width / 3.5) - 2.5;
	new[1] = py / (w->height / 2.0) - 1.0;
	iteration = 0;
	while (new[0] * new[0] + new[1] * new[1] < params[0]
											&& iteration < fractal->max_iter)
	{
		old[0] = new[0];
		old[1] = new[1];
		new[0] = old[0] * old[0] - old[1] * old[1] + cs[0];
		new[1] = 2 * old[0] * old[1] + cs[1];
		iteration++;
	}
	return (iteration);
}

int		burning_ship(t_fractal *fractal, double px, double py, t_window *w)
{
	float	*params;
	double	xy0[2];
	double	xy[2];
	double	x_temp;
	int		iteration;

	params = fractal->params;
	params[0] = 4.0;
	xy0[0] = px / (w->width / 3.5) - 2.5;
	xy0[1] = py / (w->height / 2.0) - 1.0;
	xy[0] = 0.0;
	xy[1] = 0.0;
	iteration = 0;
	while (xy[0] * xy[0] + xy[1] * xy[1] < params[0]
		&& iteration < fractal->max_iter)
	{
		x_temp = xy[0] * xy[0] - xy[1] * xy[1] + xy0[0];
		xy[1] = fabs(2 * xy[0] * xy[1] + xy0[1]);
		xy[0] = fabs(x_temp);
		iteration++;
	}
	return (iteration);
}

int		sierpinski(t_fractal *fractal, double px, double py, t_window *w)
{
	int		x;
	int		y;
	int		iteration;

	(void)w;
	(void)fractal;
	x = px;
	y = py;
	iteration = 0;
	while (x > 0 && y > 0)
	{
		if ((int)x % 3 == 1 && (int)y % 3 == 1)
			return (0);
		x /= 3;
		y /= 3;
		iteration++;
	}
	return (49);
}
