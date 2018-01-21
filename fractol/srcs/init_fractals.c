

#include "fractol.h"

void	init_fractals4(t_fractol *fractol)
{
	fractol->fractals[6] = (t_fractal) {
		.handle = NULL,
		.zoom = 1.5,
		.decal_x = -350.0,
		.decal_y = 80.0,
		.max_iter = 5,
		.params = { 20.0 },
		.update_mouse_params = 1,
		.raw = 1,
		.raw_handle = losange
	};
	fractol->fractals[7] = (t_fractal) {
		.handle = NULL,
		.zoom = 1.5,
		.decal_x = -300.0,
		.decal_y = 0.0,
		.max_iter = 1,
		.params = { 20.0 },
		.update_mouse_params = 1,
		.raw = 1,
		.raw_handle = dragon
	};
}

void	init_fractals3(t_fractol *fractol)
{
	fractol->fractals[4] = (t_fractal) {
		.handle = NULL,
		.zoom = 1.0,
		.decal_x = 0.0,
		.decal_y = 0.0,
		.max_iter = 16,
		.params = { 20.0 },
		.update_mouse_params = 1,
		.raw = 1,
		.raw_handle = tree
	};
	fractol->fractals[5] = (t_fractal) {
		.handle = NULL,
		.zoom = 1.5,
		.decal_x = -350.0,
		.decal_y = -200.0,
		.max_iter = 5,
		.params = { 20.0 },
		.update_mouse_params = 1,
		.raw = 1,
		.raw_handle = snowflake
	};
	init_fractals4(fractol);
}

void	init_fractals2(t_fractol *fractol)
{
	fractol->fractals[2] = (t_fractal) {
		.handle = burning_ship,
		.zoom = 0.8,
		.decal_x = -100.0,
		.decal_y = -300.0,
		.max_iter = 27,
		.params = { 4.0 },
		.update_mouse_params = 1,
		.raw = 0,
		.raw_handle = NULL
	};
	fractol->fractals[3] = (t_fractal) {
		.handle = sierpinski,
		.zoom = 0.1,
		.decal_x = 0.0,
		.decal_y = 0.0,
		.max_iter = 50,
		.params = { 4.0 },
		.update_mouse_params = 1,
		.raw = 0,
		.raw_handle = NULL
	};
	init_fractals3(fractol);
}

void	init_fractals(t_fractol *fractol)
{
	fractol->fractals[0] = (t_fractal) {
		.handle = mandelbrot,
		.zoom = 0.8,
		.decal_x = 0.0,
		.decal_y = -100.0,
		.max_iter = 49,
		.params = { 4.0 },
		.update_mouse_params = 1,
		.raw = 0,
		.raw_handle = NULL
	};
	fractol->fractals[1] = (t_fractal) {
		.handle = julia,
		.zoom = 0.8,
		.decal_x = 50.0,
		.decal_y = -100.0,
		.max_iter = 49,
		.params = { 4.0 },
		.update_mouse_params = 1,
		.raw = 0,
		.raw_handle = NULL
	};
	init_fractals2(fractol);
}