

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
	double	x0;
	double	y0;
	double	x;
	double	y;
	double	x_temp;
	int		iteration;

	params = fractal->params;
	params[0] = 4.0;
	x0 = px / (w->width / 3.5) - 2.5;
	y0 = py / (w->height / 2.0) - 1.0;
	x = 0.0;
	y = 0.0;
	iteration = 0;
	while (x * x + y * y < params[0] && iteration < fractal->max_iter)
	{
		x_temp = x * x - y * y + x0;
		y = fabs(2 * x * y + y0);
		x = fabs(x_temp);
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
	from_angle[0] = (f->window.width / 2) / fractal->zoom - (fractal->decal_x * fractal->zoom);
	from_angle[1] = (f->window.height / 2) / fractal->zoom - (fractal->decal_y * fractal->zoom);
	from_angle[2] = 160.0 + fractal->params[0];
	branch_len = (f->window.height / 2) * fractal->zoom;
	iter = fractal->max_iter;
	iter = iter > 21 ? 21 : iter;
	iter--;
	recursive_dragon_right(f, iter, from_angle, branch_len);
}
