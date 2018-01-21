

#include "fractol.h"

int		millis_since(struct timeval *start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return (1000 * (end.tv_sec - start->tv_sec)
		+ (end.tv_usec - start->tv_usec) / 1000);
}

void	print_time_taken(struct timeval *start, char *before, char *after)
{
	char			ms[30];
	int				time_taken;

	ft_putstr(before);
	time_taken = millis_since(start);
	ft_itoa(time_taken, ms);
	ft_putstr(ms);
	ft_putstr(" ms");
	ft_putstr(after);
}

void	render_fractol(t_fractol *fractol)
{
	apply_image_to_window(&(fractol->window));
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
	t_fractal		*fractal;

	d = (t_thread_data*)param;
	fractal = &(d->f->fractals[d->f->current_fractal]);
	y = d->from_y;
	while (y < d->until_y)
	{
		x = d->from_x;
		while (x < d->until_x)
		{
			it = fractal->handle(fractal, x / fractal->zoom + fractal->decal_x,
				y / fractal->zoom + fractal->decal_y, &(d->f->window)
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

void	wait_for_threads_to_finish(pthread_t *threads)
{
	int		i;

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
}

void	maybe_update_fractal_params(t_fractol *fractol)
{
	t_fractal	*fractal;

	fractal = &(fractol->fractals[fractol->current_fractal]);
	if (fractal->update_mouse_params)
	{
		fractal->params[1] = fractol->window.mouse.x;
		fractal->params[2] = fractol->window.mouse.y;
	}
}

void	launch_thread(pthread_t *threads, t_thread_data *data, int i)
{
	if (pthread_create(&(threads[i]), NULL, compute_part, &(data[i])) != 0)
	{
		ft_putstr("Error while creating thread\n");
		exit(1);
	}
}

void	compute_fractol(t_fractol *fractol)
{
	struct timeval	start;
	t_thread_data	data[NB_THREADS];
	pthread_t		threads[NB_THREADS];
	int				i;

	gettimeofday(&start, NULL);
	if (fractol->fractals[fractol->current_fractal].raw)
		fractol->fractals[fractol->current_fractal].raw_handle(fractol);
	else
	{
		i = 0;
		while (i < NB_THREADS)
		{
			data[i].f = fractol;
			data[i].from_x = fractol->window.width / NB_THREADS * i;
			data[i].until_x = fractol->window.width / NB_THREADS * (i + 1);
			data[i].from_y = 0;
			data[i].until_y = fractol->window.height;
			launch_thread(threads, data, i);
			i++;
		}
		wait_for_threads_to_finish(threads);
	}
	print_time_taken(&start, "Computing took ", "\n");
}

char	init_fractol(t_fractol *fractol, int width, int height, char *title)
{
	fractol->changed = 1;
	fractol->current_fractal = 0;
	init_fractals(fractol);
	gettimeofday(&(fractol->last_frame), NULL);

	fractol->current_palette = 0;
	fractol->big_mode = 0;
	init_palettes(fractol->palettes);
	if (!(init_window(&(fractol->window), width, height, title)))
	{
		ft_putstr("Could not initialize window\n");
		return (0);
	}
	mlx_expose_hook(fractol->window.win, expose_hook, (void*)fractol);
	mlx_mouse_hook(fractol->window.win, mouse_hook, (void*)fractol);
	mlx_hook(fractol->window.win, 6, 1L<<6, mouse_move_hook, (void*)fractol);
	mlx_hook(fractol->window.win, 2, 1,
										key_pressed_hook, (void*)fractol);
	mlx_hook(fractol->window.win, 3, 2,
										key_released_hook, (void*)fractol);
	return (1);
}

void	update_values_with_input(t_fractol *fractol)
{
	float		delta;
	t_fractal	*fractal;

	fractal = &(fractol->fractals[fractol->current_fractal]);
	delta = millis_since(&(fractol->last_frame));
	delta /= 30.0;
	if (fractol->window.pressed_keys[0])
		fractal->decal_y -= (20.0 * delta) / fractal->zoom;
	if (fractol->window.pressed_keys[1])
		fractal->decal_x -= (20.0 * delta) / fractal->zoom;
	if (fractol->window.pressed_keys[2])
		fractal->decal_y += (20.0 * delta) / fractal->zoom;
	if (fractol->window.pressed_keys[3])
		fractal->decal_x += (20.0 * delta) / fractal->zoom;
	if (fractol->window.pressed_keys[4])
		fractal->params[0] *= (1.0 + (delta / 20));
	if (fractol->window.pressed_keys[5])
		fractal->params[0] *= (1.0 - (delta / 20));
	if (fractol->window.pressed_keys[6])
		zoom_on_mouse(fractal, 1.05, fractol);
	if (fractol->window.pressed_keys[7])
		zoom_on_mouse(fractal, 0.95, fractol);
}

int		loop(void *param)
{
	t_fractol	*fractol;
	int			i;
	char		key_pressed;

	fractol = (t_fractol*)param;
	key_pressed = 0;
	i = 0;
	while (i < NB_KEY_PRESS)
	{
		if (fractol->window.pressed_keys[i])
			key_pressed = 1;
		i++;
	}
	if (!fractol->changed && !key_pressed)
	{
		gettimeofday(&(fractol->last_frame), NULL);
		return (0);
	}
	fractol->changed = 0;
	if (key_pressed)
		update_values_with_input(fractol);
	maybe_update_fractal_params(fractol);
	gettimeofday(&(fractol->last_frame), NULL);
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
	if (!init_fractol(&fractol, width, height, "fractol - dbousque"))
		return (1);
	maybe_update_current_fractal(&fractol, argc, argv);
	mlx_loop_hook(fractol.window.mlx, loop, (void*)&fractol);
	mlx_loop(fractol.window.mlx);
	return (0);
}
