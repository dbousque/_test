

#include "fractol.h"

int		colors[] = {
	0x000000,
	0x111111,
	0x222222,
	0x333333,
	0x444444,
	0x555555,
	0x666666,
	0x777777,
	0x888888,
	0x999999,
	0xa0a0a0,
	0xb0b0b0,
	0xc0c0c0,
	0xd0d0d0,
	0xe0e0e0,
	0xf0f0f0,
	0xf2f2f2,
	0xf4f4f4,
	0xf6f6f6,
	0xf8f8f8,
	0xfafafa,
	0xfbfbfb,
	0xfcfcfc,
	0xfdfdfd,
	0xfefefe,
	0xffffff,
	0xc0c0c0,
	0xc0c0c0,
	0xc0c0c0,
};

int		mandelbrot(t_fractal *fractal, int x, int y, t_window *window)
{
	t_mouse		*mouse;
	int			width;
	int			height;
	float		*params;

	mouse = &(window->mouse);
	width = window->width;
	height = window->height;
	params = fractal->params;
	float x0 = x / (width / 3.5) - 2.5;
	float y0 = y / (height / 2.0) - 1.0;
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
	return (colors[iteration]);
}