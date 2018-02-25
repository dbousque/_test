

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

char	interpret_err(t_wolf3d *wolf3d, char *msg)
{
	free(wolf3d->map.textures.elts);
	free(wolf3d->map.blocks.elts);
	free(wolf3d->map.blocks_positions.elts);
	ft_putstr(msg);
	return (0);
}

char	populate_texture(t_value *json_texture, t_texture *texture)
{
	(void)json_texture;
	(void)texture;
	return (1);
}

char	interpret_map_file(t_wolf3d *wolf3d, t_value *map_json)
{
	t_value		*textures;
	t_texture	*tmp_texture;
	int		i;

	ft_putstr("Reading map file...\n");
	if (map_json->type != DICT)
		return (interpret_err(wolf3d, "File is not a JSON object\n"));
	textures = get_val(map_json, "textures");
	if (!textures)
		return (interpret_err(wolf3d, "Missing \"textures\" field\n"));
	if (textures->type != ARRAY)
		return (interpret_err(wolf3d, "\"textures\" field is not an array\n"));
	i = 0;
	while (get_tab(textures)[i])
	{
		if (get_tab(textures)[i]->type != DICT)
			return (interpret_err(wolf3d, "a texture is not an object\n"));
		if (!get_val(get_tab(textures)[i], "name"))
			return (interpret_err(wolf3d, "a texture does not have a name\n"));
		if (!get_val(get_tab(textures)[i], "file"))
			return (interpret_err(wolf3d, "a texture does not have a file\n"));
		if (get_val(get_tab(textures)[i], "name")->type != STRING)
			return (interpret_err(wolf3d, "a texture's name is not string\n"));
		if (get_val(get_tab(textures)[i], "file")->type != STRING)
			return (interpret_err(wolf3d, "a texture's file is not string\n"));
		if (!(tmp_texture = new_elt(&(wolf3d->map.textures))))
			return (interpret_err(wolf3d, "malloc error\n"));
		if (!populate_texture(get_tab(textures)[i], tmp_texture))
			return (interpret_err(wolf3d, "invalid texture\n"));
		i++;
	}
	ft_putstr("done\n");
	return (1);
}

char	init_wolf3d(t_wolf3d *wolf3d, t_value *map_json)
{
	wolf3d->changed = 1;
	gettimeofday(&(wolf3d->last_frame), NULL);
	wolf3d->player.looking_dir = 90.0;
	if (!(init_list(&(wolf3d->map.textures), sizeof(t_texture))))
		return (0);
	if (!(init_list(&(wolf3d->map.blocks), sizeof(t_block))))
		return (0);
	if (!(init_list(&(wolf3d->map.blocks_positions), sizeof(int))))
		return (0);
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

t_value	*read_json_file(char *filename)
{
	t_value		*map_json;

	if (!(map_json = read_json(filename)))
	{
		ft_putstr("Failed to read file \"");
		ft_putstr(filename);
		ft_putstr("\"\n");
		return (NULL);
	}
	if (map_json->type == 0)
	{
		ft_putstr("Invalid JSON file\n");
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
