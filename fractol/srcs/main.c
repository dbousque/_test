

#include "fractol.h"

void	print_time_taken(struct timeval *start, char *before, char *after)
{
	char			ms[30];
	int				time_taken;
	struct timeval	end;

	gettimeofday(&end, NULL);
	ft_putstr(before);
	time_taken = 1000 * (end.tv_sec - start->tv_sec)
		+ (end.tv_usec - start->tv_usec) / 1000;
	ft_itoa(time_taken, ms);
	ft_putstr(ms);
	ft_putstr(" ms");
	ft_putstr(after);
}

void	render_fractol(t_fractol *fractol)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	apply_image_to_window(&(fractol->window));
	print_time_taken(&start, "Apply took ", "\n");
}

void	compute_fractol(t_fractol *fractol)
{
	int				x;
	int				y;
	int				color;
	struct timeval	start;

	gettimeofday(&start, NULL);
	y = 0;
	while (y < fractol->window.height)
	{
		x = 0;
		while (x < fractol->window.width)
		{
			color = fractol->fractals[fractol->current_fractal].handle(
				&(fractol->fractals[fractol->current_fractal]),
				x,
				y,
				&(fractol->window)
			);
			PIXEL_AT(fractol->window, x, y) = color;
			x++;
		}
		y++;
	}
	print_time_taken(&start, "Computing took ", "\n");
}

char	init_fractol(t_fractol *fractol, int width, int height, char *title)
{
	fractol->changed = 1;
	fractol->current_fractal = 0;
	fractol->fractals[0].handle = mandelbrot;
	fractol->fractals[0].max_iter = 12;
	fractol->fractals[0].params[0] = 4.0;
	if (!(init_window(&(fractol->window), width, height, title)))
	{
		ft_putstr("Could not initialize window\n");
		return (0);
	}
	return (1);
}

int		loop(void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol*)param;
	if (!fractol->changed)
		return (0);
	fractol->changed = 0;
	compute_fractol(fractol);
	render_fractol(fractol);
	return (0);
}

int		main(int argc, char **argv)
{
	t_fractol	fractol;
	int			width;
	int			height;

	parse_opts(argc, argv, &width, &height);
	if (!init_fractol(&fractol, width, height, "Helloz"))
		return (1);
	maybe_update_current_fractal(&fractol, argc, argv);
	mlx_loop_hook(fractol.window.mlx, loop, (void*)&fractol);
	mlx_loop(fractol.window.mlx);
	return (0);
}
