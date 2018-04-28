/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals_non_std.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:32:01 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 14:32:03 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	recursive_tree(t_fractol *frac, int iter, double from_angle[3],
														double branch_len)
{
	double		angle;
	double		from[2];
	double		to[2];

	if (iter >= frac->fractals[frac->current_fractal].max_iter || iter >= 20)
		return ;
	angle = from_angle[2];
	from[0] = from_angle[0];
	from[1] = from_angle[1];
	to[0] = from[0] + (branch_len * cos(DEG_TO_RAD(angle)));
	to[1] = from[1] - (branch_len * sin(DEG_TO_RAD(angle)));
	draw_line(frac, from, to, iter);
	from_angle[0] = to[0];
	from_angle[1] = to[1];
	from_angle[2] = angle + (frac->fractals[frac->current_fractal].params[0]);
	recursive_tree(frac, iter + 1, from_angle, branch_len / 2);
	from_angle[0] = to[0];
	from_angle[1] = to[1];
	from_angle[2] = angle - (frac->fractals[frac->current_fractal].params[0]);
	recursive_tree(frac, iter + 1, from_angle, branch_len / 2);
}

void	tree(t_fractol *fractol)
{
	double		from_angle[3];
	t_fractal	*fractal;
	double		branch_len;

	clear_screen(fractol);
	fractal = &(fractol->fractals[fractol->current_fractal]);
	from_angle[0] = (fractol->window.width / 2) / fractal->zoom
										- (fractal->decal_x * fractal->zoom);
	from_angle[1] = fractol->window.height / fractal->zoom
										- (fractal->decal_y * fractal->zoom);
	from_angle[2] = 90.0;
	branch_len = (fractol->window.height / 2) * fractal->zoom;
	recursive_tree(fractol, 0, from_angle, branch_len);
}

void	recursive_snowflake(t_fractol *frac, int iter, double from_angle[3],
															double branch_len)
{
	double		angle;
	double		from[2];
	double		to[2];

	angle = from_angle[2];
	if (iter >= frac->fractals[frac->current_fractal].max_iter || iter >= 10)
	{
		from[0] = from_angle[0];
		from[1] = from_angle[1];
		to[0] = from[0] + (branch_len * cos(DEG_TO_RAD(angle)));
		to[1] = from[1] - (branch_len * sin(DEG_TO_RAD(angle)));
		from_angle[0] = to[0];
		from_angle[1] = to[1];
		return (draw_line(frac, from, to, 49));
	}
	recursive_snowflake(frac, iter + 1, from_angle, branch_len / 3);
	from_angle[2] = angle + 60.0;
	recursive_snowflake(frac, iter + 1, from_angle, branch_len / 3);
	from_angle[2] = angle - 60.0;
	recursive_snowflake(frac, iter + 1, from_angle, branch_len / 3);
	from_angle[2] = angle;
	recursive_snowflake(frac, iter + 1, from_angle, branch_len / 3);
}

void	snowflake(t_fractol *f)
{
	double		from_angle[3];
	t_fractal	*fractal;
	double		branch_len;

	clear_screen(f);
	fractal = &(f->fractals[f->current_fractal]);
	from_angle[0] = (f->window.width / 2) / fractal->zoom
										- (fractal->decal_x * fractal->zoom);
	from_angle[1] = (f->window.height / 2) / fractal->zoom
										- (fractal->decal_y * fractal->zoom);
	from_angle[2] = 160.0 + fractal->params[0];
	branch_len = (f->window.height / 2) * fractal->zoom;
	recursive_snowflake(f, 1, from_angle, branch_len);
	from_angle[2] -= 120.0;
	recursive_snowflake(f, 1, from_angle, branch_len);
	from_angle[2] -= 120.0;
	recursive_snowflake(f, 1, from_angle, branch_len);
}

void	losange(t_fractol *f)
{
	double		from_angle[3];
	t_fractal	*fractal;
	double		branch_len;

	clear_screen(f);
	fractal = &(f->fractals[f->current_fractal]);
	from_angle[0] = (f->window.width / 2) / fractal->zoom
										- (fractal->decal_x * fractal->zoom);
	from_angle[1] = (f->window.height / 2) / fractal->zoom
										- (fractal->decal_y * fractal->zoom);
	from_angle[2] = 160.0 + fractal->params[0];
	branch_len = (f->window.height / 2) * fractal->zoom;
	recursive_snowflake(f, 1, from_angle, branch_len);
	from_angle[2] = 300.0;
	recursive_snowflake(f, 1, from_angle, branch_len);
	from_angle[2] = 60.0;
	recursive_snowflake(f, 1, from_angle, branch_len);
}
