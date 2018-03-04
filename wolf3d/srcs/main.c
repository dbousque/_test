

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

void	draw_empty_column(t_wolf3d *wolf3d, int pixel_x)
{
	int		y;

	y = 0;
	while (y < wolf3d->window.height / 2)
	{
		set_color_at(wolf3d, pixel_x, y, 0xbecee8);
		y++;
	}
	while (y < wolf3d->window.height)
	{
		set_color_at(wolf3d, pixel_x, y, 0x000000);
		y++;
	}
}

void	draw_mock_column(t_wolf3d *wolf3d, int pixel_x, float distance)
{
	int		rgb;
	float	height_at_zero;
	float	full_screen_point;
	float	block_height;
	int		block_until;
	int		y;

	//ft_printf("distance %.2f\n", distance);
	//ft_printf("player at %.2f %.2f\n", wolf3d->player.x, wolf3d->player.y);
	height_at_zero = 2.0;
	full_screen_point = 1.3 - ((wolf3d->opts.fov - 40.0) / 100.0);
	block_height = height_at_zero / (distance / full_screen_point);
	//rgb = (random() % 256) + (random() % 256 * 256) + (random() % 256 * 65536);
	rgb = 0xf2df4d;
	block_until = (wolf3d->window.height / 2) * block_height;
	if (block_until > wolf3d->window.height / 2)
		block_until = wolf3d->window.height / 2;
	y = 0;
	while (y < (wolf3d->window.height / 2 - block_until))
	{
		set_color_at(wolf3d, pixel_x, y, 0xbecee8);
		y++;
	}
	while (y < wolf3d->window.height / 2)
	{
		set_color_at(wolf3d, pixel_x, y, rgb);
		y++;
	}
	while (y < (wolf3d->window.height / 2 + block_until))
	{
		set_color_at(wolf3d, pixel_x, y, rgb);
		y++;
	}
	while (y < wolf3d->window.height)
	{
		set_color_at(wolf3d, pixel_x, y, 0x000000);
		y++;
	}
}

void	set_x_y_steps(float x, float y, float decals[2], float x_y_steps[2])
{
	x_y_steps[0] = FLT_MAX;
	x_y_steps[1] = FLT_MAX;
	if (decals[0] != 0.0)
	{
		x_y_steps[0] = -(x - ((int)x + 1));
		if (decals[0] < 0.0)
			x_y_steps[0] = x - (int)x;
	}
	if (decals[1] != 0.0)
	{
		x_y_steps[1] = -(y - ((int)y + 1));
		if (decals[1] < 0.0)
			x_y_steps[1] = y - (int)y;
	}
}

void	advance_to_next_block(float x_y[2], float decals[2],
									float x_y_steps[2], int blocks_x_y[2])
{
	if (fabsf(x_y_steps[0] / decals[0]) < fabsf(x_y_steps[1] / decals[1]))
	{
		blocks_x_y[0] = (int)x_y[0] + (decals[0] < 0.0 ? -1 : 1);
		x_y[0] = blocks_x_y[0];
		x_y[1] += decals[1] * fabsf(x_y_steps[0] / decals[0]);
		blocks_x_y[1] = (int)x_y[1];
	}
	else
	{
		blocks_x_y[1] = (int)x_y[1] + (decals[1] < 0.0 ? -1 : 1);
		x_y[1] = blocks_x_y[1];
		x_y[0] += decals[0] * fabsf(x_y_steps[1] / decals[1]);
		blocks_x_y[0] = (int)x_y[0];
	}
}

void	send_ray_in_dir(t_wolf3d *wolf3d, float direction, int pixel_x)
{
	float		x_y[2];
	int			blocks_x_y[2];
	float		decals[2];
	float		x_y_steps[2];
	t_block		*block;

	block = NULL;
	x_y[0] = wolf3d->player.x;
	x_y[1] = wolf3d->player.y;
	decals[0] = cosf(DEG_TO_RAD(direction));
	decals[1] = sinf(DEG_TO_RAD(direction));
	while (1)
	{
		set_x_y_steps(x_y[0], x_y[1], decals, x_y_steps);
		advance_to_next_block(x_y, decals, x_y_steps, blocks_x_y);
		if (blocks_x_y[0] < 0 || blocks_x_y[0] > wolf3d->map.width ||
			blocks_x_y[1] < 0 || blocks_x_y[1] > wolf3d->map.height)
		{
			break ;
		}
		if ((block = BLOCK_AT(wolf3d, blocks_x_y[0], blocks_x_y[1])))
			break ;
	}
	if (!block)
	{
		draw_empty_column(wolf3d, pixel_x);
		return ;
	}
	//ft_printf("block    %d %d\n", blocks_x_y[0], blocks_x_y[1]);
	//ft_printf("block at %.2f %.2f\n", x_y[0], x_y[1]);
	//((t_block**)wolf3d->map.blocks_positions.elts)
	float distance = fabsf(wolf3d->player.x - x_y[0]) + fabsf(wolf3d->player.y - x_y[1]);
	draw_mock_column(wolf3d, pixel_x, distance);
}

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
	int				x;
	int				step;
	float			dir;

	gettimeofday(&start, NULL);
	step = wolf3d->opts.big_mode ? 4 : 1;
	x = 0;
	while (x < wolf3d->window.width)
	{
		dir = ((float)x / wolf3d->window.width) * wolf3d->opts.fov;
		dir -= wolf3d->opts.fov / 2;
		send_ray_in_dir(wolf3d, wolf3d->player.looking_dir + dir, x);
		x += step;
	}
	print_time_taken(&start, "Computing took ", "\n");
}

char	init_wolf3d(t_wolf3d *wolf3d, t_value *map_json)
{
	wolf3d->changed = 1;
	gettimeofday(&(wolf3d->last_frame), NULL);
	wolf3d->player.looking_dir = 270.0;
	wolf3d->opts.big_mode = 0;
	wolf3d->opts.fov = 90.0;
	init_list(&(wolf3d->map.textures), sizeof(t_texture));
	init_list(&(wolf3d->map.blocks), sizeof(t_block));
	init_list(&(wolf3d->map.blocks_positions), sizeof(t_block*));
	return (interpret_map_file(wolf3d, map_json));
}

char	init_wolf3d_win(t_wolf3d *wolf3d, int width, int height, char *title)
{
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
	//if (fractol->window.pressed_keys[4])
	//	fractal->params[0] *= (1.0 + (delta / 20));
	if (wolf3d->window.pressed_keys[0])
		wolf3d->player.y -= 2.0 * (delta / 1000.0);
	if (wolf3d->window.pressed_keys[1])
		wolf3d->player.y += 2.0 * (delta / 1000.0);
	if (wolf3d->window.pressed_keys[2])
		wolf3d->player.x += 2.0 * (delta / 1000.0);
	if (wolf3d->window.pressed_keys[3])
		wolf3d->player.x -= 2.0 * (delta / 1000.0);
	if (wolf3d->window.pressed_keys[4])
		wolf3d->player.looking_dir -= 90.0 * (delta / 1000.0);
	if (wolf3d->window.pressed_keys[5])
		wolf3d->player.looking_dir += 90.0 * (delta / 1000.0);
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

t_value	*read_json_file(char *filename)
{
	t_value		*map_json;

	if (!(map_json = read_json(filename, 20 * 1024 * 1024)))
	{
		ft_putstr("Failed to read file \"");
		ft_putstr(filename);
		ft_putstr("\"\n");
		return (NULL);
	}
	if (map_json->type == 0)
	{
		ft_putstr("Invalid JSON file\n");
		free_value(map_json);
		return (NULL);
	}
	return (map_json);
}

int		main(int argc, char **argv)
{
	t_wolf3d	wolf3d;
	int			width;
	int			height;
	t_value		*map_json;

	if (argc <= 1)
	{
		ft_putstr("Usage : ");
		ft_putstr(argv[0]);
		ft_putstr(" <map_file>\n");
		return (0);
	}
	if (!(map_json = read_json_file(argv[1])))
		return (1);
	if (!init_wolf3d(&wolf3d, map_json))
	{
		free_value(map_json);
		return (1);
	}
	free_value(map_json);
	width = DEFAULT_WIDTH;
	height = DEFAULT_HEIGHT;
	if (!init_wolf3d_win(&wolf3d, width, height, "wolf3d - dbousque"))
		return (1);
	mlx_loop_hook(wolf3d.window.mlx, loop, (void*)&wolf3d);
	mlx_loop(wolf3d.window.mlx);
	return (0);
}
