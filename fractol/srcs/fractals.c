

#include "fractol.h"

int		mandelbrot(t_fractal *fractal, float x, float y, t_dims *dimensions)
{
	float		*params;
	float		decals[3];
	float		_x;
	float		_y;
	int			iteration;

	params = fractal->params;
	decals[0] = x / (dimensions->width / 3.0) - 2.5;
	decals[1] = y / (dimensions->height / 2.0) - 1.0;
	_x = 0.0;
	_y = 0.0;
	iteration = 0;
	while (_x*_x + _y*_y < params[0] && iteration < fractal->max_iter)
	{
		decals[2] = _x*_x - _y*_y + decals[0];
		_y = 2*_x*_y + decals[1];
		_x = decals[2];
		iteration++;
	}
	return (iteration);
}

int		modulo(t_fractal *fractal, float x, float y, t_dims *dimensions)
{
	float		*params;
	float		decals[3];
	float		_x;
	float		_y;
	int			iteration;

	params = fractal->params;
	decals[0] = x / (dimensions->width / 3.5) - 2.5;
	decals[1] = y / (dimensions->height / 2.0) - 1.0;
	_x = 0.0;
	_y = 0.0;
	iteration = 0;
	while (_x*_x * _y*_y < params[0] && iteration < fractal->max_iter)
	{
		decals[2] = _x*_x - _y*_y + decals[0];
		_y = 2*_x*_y + decals[1];
		_x = decals[2];
		iteration++;
	}
	return (iteration);
}
