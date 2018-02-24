

#include "wolf3d.h"

void	render_wolf3d(t_wolf3d *wolf3d)
{
	apply_image_to_window(&(wolf3d->window));
}

/*void	launch_thread(pthread_t *threads, t_thread_data *data, int i)
{
	if (pthread_create(&(threads[i]), NULL, compute_part, &(data[i])) != 0)
	{
		ft_putstr("Error while creating thread\n");
		exit(1);
	}
}*/

void	compute_wolf3d(t_wolf3d *wolf3d)
{
	/*struct timeval	start;
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
	print_time_taken(&start, "Computing took ", "\n");*/

	struct timeval	start;

	gettimeofday(&start, NULL);
	(void)wolf3d;
	print_time_taken(&start, "Computing took ", "\n");
}

char	init_wolf3d(t_wolf3d *wolf3d, int width, int height, char *title)
{
	wolf3d->changed = 1;
	gettimeofday(&(wolf3d->last_frame), NULL);

	if (!(init_window(&(wolf3d->window), width, height, title)))
	{
		ft_putstr("Could not initialize window\n");
		return (0);
	}
	mlx_expose_hook(wolf3d->window.win, expose_hook, (void*)wolf3d);
	mlx_mouse_hook(wolf3d->window.win, mouse_hook, (void*)wolf3d);
	mlx_hook(wolf3d->window.win, 6, 1L<<6, mouse_move_hook, (void*)wolf3d);
	mlx_hook(wolf3d->window.win, 2, 1, key_pressed_hook, (void*)wolf3d);
	mlx_hook(wolf3d->window.win, 3, 2, key_released_hook, (void*)wolf3d);
	return (1);
}

void	update_values_with_input(t_wolf3d *wolf3d)
{
	float		delta;

	delta = millis_since(&(wolf3d->last_frame));
	delta /= 30.0;
	//if (fractol->window.pressed_keys[4])
	//	fractal->params[0] *= (1.0 + (delta / 20));
	(void)delta;
}

int		loop(void *param)
{
	t_wolf3d	*wolf3d;
	int			i;
	char		key_pressed;

	wolf3d = (t_wolf3d*)param;
	key_pressed = 0;
	i = 0;
	while (i < NB_KEY_PRESS)
	{
		if (wolf3d->window.pressed_keys[i])
			key_pressed = 1;
		i++;
	}
	if (!wolf3d->changed && !key_pressed)
	{
		gettimeofday(&(wolf3d->last_frame), NULL);
		return (0);
	}
	wolf3d->changed = 0;
	if (key_pressed)
		update_values_with_input(wolf3d);
	gettimeofday(&(wolf3d->last_frame), NULL);
	compute_wolf3d(wolf3d);
	render_wolf3d(wolf3d);
	return (0);
}

int		main(int argc, char **argv)
{
	t_wolf3d	wolf3d;
	int			width;
	int			height;

	(void)argc;
	(void)argv;
	width = DEFAULT_WIDTH;
	height = DEFAULT_HEIGHT;
	if (!init_wolf3d(&wolf3d, width, height, "wolf3d - dbousque"))
		return (1);
	mlx_loop_hook(wolf3d.window.mlx, loop, (void*)&wolf3d);
	mlx_loop(wolf3d.window.mlx);
	return (0);
}
