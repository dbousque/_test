

#include "fractol.h"

int		mandelbrot(t_fractal *fractal, int x, int y, t_window *window)
{
	t_mouse		*mouse;
	float		*params;

	mouse = &(window->mouse);
	params = fractal->params;
	float x0 = x / (window->width / 3.5) - 2.5;
	float y0 = y / (window->height / 2.0) - 1.0;
	float _x = 0.0;
	float _y = 0.0;
	int iteration = 0;
	while (_x*_x + _y*_y < params[0] && iteration < fractal->max_iter)
	{
		float xtemp = _x*_x - _y*_y + x0;
		_y = 2*_x*_y + y0;
		_x = xtemp;
		iteration++;
	}
	return (iteration);
}