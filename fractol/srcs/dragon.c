/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:31:20 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 14:31:22 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	rdl_draw(t_fractol *frac, double from_angle[3], double branch_len)
{
	double		from[2];
	double		to[2];

	from_angle[2] -= 45.0;
	from[0] = from_angle[0];
	from[1] = from_angle[1];
	to[0] = from[0] + (branch_len * cos(DEG_TO_RAD(from_angle[2])));
	to[1] = from[1] - (branch_len * sin(DEG_TO_RAD(from_angle[2])));
	draw_line(frac, from, to, 49);
	from_angle[2] += 90.0;
	from[0] = to[0];
	from[1] = to[1];
	to[0] = from[0] + (branch_len * cos(DEG_TO_RAD(from_angle[2])));
	to[1] = from[1] - (branch_len * sin(DEG_TO_RAD(from_angle[2])));
	draw_line(frac, from, to, 49);
	from_angle[0] = to[0];
	from_angle[1] = to[1];
	from_angle[2] -= 45.0;
}

void	recursive_dragon_left(t_fractol *frac, int iter, double from_angle[3],
															double branch_len)
{
	iter--;
	branch_len /= 1.41421;
	if (iter > 0)
	{
		from_angle[2] -= 45.0;
		recursive_dragon_right(frac, iter, from_angle, branch_len);
		from_angle[2] += 90.0;
		recursive_dragon_left(frac, iter, from_angle, branch_len);
		from_angle[2] -= 45.0;
		return ;
	}
	rdl_draw(frac, from_angle, branch_len);
}

void	rdr_draw(t_fractol *frac, double from_angle[3], double branch_len)
{
	double		from[2];
	double		to[2];

	from_angle[2] += 45.0;
	from[0] = from_angle[0];
	from[1] = from_angle[1];
	to[0] = from[0] + (branch_len * cos(DEG_TO_RAD(from_angle[2])));
	to[1] = from[1] - (branch_len * sin(DEG_TO_RAD(from_angle[2])));
	draw_line(frac, from, to, 49);
	from_angle[2] -= 90.0;
	from[0] = to[0];
	from[1] = to[1];
	to[0] = from[0] + (branch_len * cos(DEG_TO_RAD(from_angle[2])));
	to[1] = from[1] - (branch_len * sin(DEG_TO_RAD(from_angle[2])));
	draw_line(frac, from, to, 49);
	from_angle[0] = to[0];
	from_angle[1] = to[1];
	from_angle[2] += 45.0;
}

void	recursive_dragon_right(t_fractol *frac, int iter, double from_angle[3],
															double branch_len)
{
	iter--;
	branch_len /= 1.41421;
	if (iter > 0)
	{
		from_angle[2] += 45.0;
		recursive_dragon_right(frac, iter, from_angle, branch_len);
		from_angle[2] -= 90.0;
		recursive_dragon_left(frac, iter, from_angle, branch_len);
		from_angle[2] += 45.0;
		return ;
	}
	rdr_draw(frac, from_angle, branch_len);
}

void	dragon(t_fractol *f)
{
	double		from_angle[3];
	t_fractal	*fractal;
	double		branch_len;
	int			iter;

	clear_screen(f);
	fractal = &(f->fractals[f->current_fractal]);
	from_angle[0] = (f->window.width / 2) / fractal->zoom -
		(fractal->decal_x * fractal->zoom);
	from_angle[1] = (f->window.height / 2) / fractal->zoom -
		(fractal->decal_y * fractal->zoom);
	from_angle[2] = 160.0 + fractal->params[0];
	branch_len = (f->window.height / 2) * fractal->zoom;
	iter = fractal->max_iter;
	iter = iter > 21 ? 21 : iter;
	iter--;
	recursive_dragon_right(f, iter, from_angle, branch_len);
}
