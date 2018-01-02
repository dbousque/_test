

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
	while (new[0] * new[0] + new[1] * new[1] < params[0] && iteration < fractal->max_iter)
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
