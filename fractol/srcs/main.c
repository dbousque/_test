

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

void	set_color_at(t_fractol *fractol, int x, int y, int color)
{
	PIXEL_AT(fractol->window, x, y) = color;
	if (fractol->big_mode)
	{
		PIXEL_AT(fractol->window, x + 1, y) = color;
		PIXEL_AT(fractol->window, x, y + 1) = color;
		PIXEL_AT(fractol->window, x + 1, y + 1) = color;
	}
}

void	*compute_part(void *param)
{
	int				x;
	int				y;
	int				it;
	int				co;
	t_thread_data	*d;

	d = (t_thread_data*)param;
	y = d->from_y;
	while (y < d->until_y)
	{
		x = d->from_x;
		while (x < d->until_x)
		{
			it = d->f->fractals[d->f->current_fractal].handle(
				&(d->f->fractals[d->f->current_fractal]),
				x,
				y,
				&(d->f->window)
			);
			co = d->f->palettes[d->f->current_palette][it % PALETTE_LEN];
			co = it == d->f->fractals[d->f->current_fractal].max_iter ? 0 : co;
			set_color_at(d->f, x, y, co);
			x += 1 + d->f->big_mode;
		}
		y += 1 + d->f->big_mode;
	}
	return (NULL);
}

void	compute_fractol(t_fractol *fractol)
{
	struct timeval	start;
	t_thread_data	data[NB_THREADS];
	pthread_t		threads[NB_THREADS];
	int				i;

	gettimeofday(&start, NULL);
	i = 0;
	while (i < NB_THREADS)
	{
		data[i].f = fractol;
		data[i].from_x = fractol->window.width / NB_THREADS * i;
		data[i].until_x = fractol->window.width / NB_THREADS * (i + 1);
		data[i].from_y = 0;
		data[i].until_y = fractol->window.height;
		if (pthread_create(&(threads[i]), NULL, compute_part, &(data[i])) != 0)
		{
			ft_putstr("Error while creating thread\n");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < NB_THREADS)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			ft_putstr("Error while waiting for thread\n");
			exit(1);
		}
		i++;
	}
	print_time_taken(&start, "Computing took ", "\n");
}

char	init_fractol(t_fractol *fractol, int width, int height, char *title)
{
	fractol->changed = 1;
	fractol->current_fractal = 0;
	fractol->fractals[0].handle = mandelbrot;
	fractol->fractals[0].max_iter = 49;
	fractol->fractals[0].params[0] = 4.0;
	fractol->current_palette = 0;
	fractol->big_mode = 0;
	init_palettes(fractol->palettes);
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
