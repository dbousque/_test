

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

int		addr_to_c(t_texture *texture, unsigned char *addr, int ori)
{
	int		res;
	float	ratio;

	ratio = 0.0;
	res = 0;
	if (texture->pixel_width == 4)
	{
		ratio = ((float)*(addr + 3)) / 256.0;
		ratio = 1.0 - ratio;
		res = (int)(((float)*(((unsigned char*)&ori) + 2)) * ratio);
		res *= 256;
		res += (int)(((float)*(((unsigned char*)&ori) + 1)) * ratio);
		res *= 256;
		res += (int)(((float)*(((unsigned char*)&ori) + 0)) * ratio);
	}
	res += (int)(((float)*(addr + 2)) * (1.0 - ratio)) * 256 * 256;
	res += (int)(((float)*(addr + 1)) * (1.0 - ratio)) * 256;
	res += (int)(((float)*(addr + 0)) * (1.0 - ratio));
	return (res);
}

void	draw_texture(t_wolf3d *wolf3d, int pixel_x, t_ray_result *ray_res,
															int block_until)
{
	int			start_y;
	int			i;
	int			color;
	t_texture	*text;
	int			is[2];

	if (ray_res->decal_in_face < 0.0 || ray_res->decal_in_face > 1.0)
		return ;
	start_y = wolf3d->window.height / 2 - block_until;
	if (ray_res->block->is_object)
		text = ray_res->block->obj_texture;
	else
		text = ray_res->block->faces[ray_res->face];
	is[0] = (int)(ray_res->decal_in_face * (float)text->width);
	is[0] *= text->pixel_width;
	i = start_y < 0 ? -start_y : 0;
	while (i < block_until * 2 && start_y + i < wolf3d->window.height)
	{
		is[1] = ((float)i / (block_until * 2)) * text->height;
		is[1] *= text->pixel_width;
		color = addr_to_c(
			text,
			&(text->pixels[is[0] + is[1] * text->width]),
			PIXEL_AT(wolf3d->window, pixel_x, start_y + i)
		);
		set_color_at(wolf3d, pixel_x, start_y + i, color);
		i++;
	}
}

void	draw_column(t_wolf3d *wolf3d, int pixel_x, t_ray_result *ray_res)
{
	float	height_at_zero;
	float	full_screen_point;
	float	block_height;
	int		block_until;
	int		y;

	height_at_zero = 1.7;
	full_screen_point = 1.6 - ((wolf3d->opts.fov - 40.0) / 50.0);
	block_height = height_at_zero / (ray_res->distance / full_screen_point);
	//if (block_height > height_at_zero / 2)
	//	block_height = height_at_zero / 2;
	block_until = (wolf3d->window.height / 2) * block_height;
	y = 0;
	while (y < (wolf3d->window.height / 2 - block_until))
	{
		//set_color_at(wolf3d, pixel_x, y, 0xbecee8);
		y++;
	}
	if (ray_res->block)
		draw_texture(wolf3d, pixel_x, ray_res, block_until);
	y = wolf3d->window.height / 2 + block_until;
	while (y < wolf3d->window.height)
	{
		//set_color_at(wolf3d, pixel_x, y, 0x000000);
		y++;
	}
}

void	clear_column(t_wolf3d *wolf3d, int pixel_x)
{
	int		y;

	y = 0;
	while (y < wolf3d->window.height)
	{
		set_color_at(wolf3d, pixel_x, y, 0x000000);
		y++;
	}
}

void	draw_object(t_wolf3d *wolf3d, int pixel_x, t_ray_result *ray_res)
{
	float		height_at_zero;
	float		full_screen_point;
	float		block_height;
	int			block_until;
	float		from[2];

	height_at_zero = 1.7;
	full_screen_point = 1.6 - ((wolf3d->opts.fov - 40.0) / 50.0);
	block_height = height_at_zero / (ray_res->distance / full_screen_point);
	//if (block_height > height_at_zero / 2)
	//	block_height = height_at_zero / 2;
	block_until = (wolf3d->window.height / 2) * block_height;
	from[0] = ray_res->x;
	from[1] = ray_res->y;
	//clear_column(wolf3d, pixel_x);
	send_ray_in_dir(wolf3d, ray_res->direction, pixel_x, from);
	draw_texture(wolf3d, pixel_x, ray_res, block_until);
}

float	angle_of_vectors(float vec1[2], float vec2[2])
{
	float	mag_vec1;
	float	mag_vec2;
	float	dot_product;
	float	param;

	mag_vec1 = sqrt((vec1[0] * vec1[0]) + (vec1[1] * vec1[1]));
	mag_vec2 = sqrt((vec2[0] * vec2[0]) + (vec2[1] * vec2[1]));
	dot_product = (vec1[0] * vec2[0]) + (vec1[1] * vec2[1]);
	param = dot_product / (mag_vec1 * mag_vec2);
	if (param > 1.0)
		param = 1.0;
	if (param < -1.0)
		param = -1.0;
	return (acosf(param));
}

char	vector_on_the_left(float vec1[2], float vec2[2])
{
	float	angle1;
	float	angle2;
	float	diff;
	float	horizon[2];

	horizon[0] = 1.0;
	horizon[1] = 0.0;
	angle1 = RAD_TO_DEG(angle_of_vectors(horizon, vec1));
	if (vec1[1] < 0.0)
		angle1 = -angle1;
	angle2 = RAD_TO_DEG(angle_of_vectors(horizon, vec2));
	if (vec2[1] < 0.0)
		angle2 = -angle2;
	diff = angle1 - angle2;
	if (diff < -180.0)
		diff += 360.0;
	if (diff > 180.0)
		diff -= 360.0;
	if (diff > 0.0)
		return (1);
	return (0);
}

void	render_object(t_wolf3d *wolf3d, int pixel_x, t_ray_result *ray_res)
{
	float	block_center_x;
	float	block_center_y;
	float	decal;
	float	vector[2];
	float	center_vector[2];

	block_center_x = (float)ray_res->block_x + 0.5;
	block_center_y = (float)ray_res->block_y + 0.5;
	ray_res->distance =
		fabsf(wolf3d->player.x - block_center_x) *
			fabsf(wolf3d->player.x - block_center_x) +
		fabsf(wolf3d->player.y - block_center_y) *
			fabsf(wolf3d->player.y - block_center_y);
	ray_res->distance = sqrtf(ray_res->distance);
	vector[0] = cosf(DEG_TO_RAD(ray_res->direction));
	vector[1] = sinf(DEG_TO_RAD(ray_res->direction));
	normalize_decals(&(vector[0]), &(vector[1]));
	center_vector[0] = block_center_x - wolf3d->player.x;
	center_vector[1] = block_center_y - wolf3d->player.y;
	normalize_decals(&(center_vector[0]), &(center_vector[1]));
	decal =(ray_res->distance * sinf(angle_of_vectors(vector, center_vector)))
		/ sinf(DEG_TO_RAD(90.0));
	decal = vector_on_the_left(vector, center_vector) ? decal : -decal;
	ray_res->decal_in_face = ((decal * 1.7) + 1) / 2.0;
	draw_object(wolf3d, pixel_x, ray_res);
}

void	render_ray(t_wolf3d *wolf3d, int pixel_x, t_ray_result *ray_res)
{
	if (wolf3d->opts.debug_mode)
		return (render_debug_ray(wolf3d, pixel_x, ray_res));
	if (ray_res->block && ray_res->block->is_object)
		return (render_object(wolf3d, pixel_x, ray_res));
	ray_res->distance = FLT_MAX;
	if (ray_res->block)
	{
		ray_res->distance =
		fabsf(wolf3d->player.x - ray_res->x) *
			fabsf(wolf3d->player.x - ray_res->x) +
		fabsf(wolf3d->player.y - ray_res->y) *
			fabsf(wolf3d->player.y - ray_res->y);
		ray_res->distance = sqrtf(ray_res->distance);
		if (ray_res->face == 0)
			ray_res->decal_in_face = ((int)ray_res->x + 1) - ray_res->x;
		else if (ray_res->face == 1)
			ray_res->decal_in_face = ((int)ray_res->y + 1) - ray_res->y;
		else if (ray_res->face == 2)
			ray_res->decal_in_face = ray_res->x - (int)ray_res->x;
		else
			ray_res->decal_in_face = ray_res->y - (int)ray_res->y;
	}
	draw_column(wolf3d, pixel_x, ray_res);
}

void	set_x_y_steps(float x, float y, float decals[2], float x_y_steps[2])
{
	x_y_steps[0] = -(x - ((int)x + 1));
	if (decals[0] < 0.0)
		x_y_steps[0] = x - (int)x;
	x_y_steps[1] = -(y - ((int)y + 1));
	if (decals[1] < 0.0)
		x_y_steps[1] = y - (int)y;
}

void	advance_to_next_block(t_ray_result *ray_res, float decals[2],
														float x_y_steps[2])
{
	float	advance_by;

	if (fabsf(x_y_steps[0] / decals[0]) < fabsf(x_y_steps[1] / decals[1]))
	{
		advance_by = fabsf(x_y_steps[0] / decals[0]);
		ray_res->face = decals[0] >= 0.0 ? 3 : 1;
	}
	else
	{
		advance_by = fabsf(x_y_steps[1] / decals[1]);
		ray_res->face = decals[1] >= 0.0 ? 0 : 2;
	}
	advance_by += 0.0001;
	ray_res->x += decals[0] * advance_by;
	ray_res->y += decals[1] * advance_by;
	ray_res->block_x = (int)ray_res->x;
	ray_res->block_y = (int)ray_res->y;
}

void	send_ray_in_dir(t_wolf3d *wolf3d, float direction, int pixel_x,
																float from[2])
{
	t_ray_result	ray_res;
	float			decals[2];
	float			x_y_steps[2];

	ray_res.block = NULL;
	ray_res.x = from[0];
	ray_res.y = from[1];
	ray_res.direction = direction;
	decals[0] = cosf(DEG_TO_RAD(direction));
	decals[1] = sinf(DEG_TO_RAD(direction));
	normalize_decals(&(decals[0]), &(decals[1]));
	while (1)
	{
		set_x_y_steps(ray_res.x, ray_res.y, decals, x_y_steps);
		advance_to_next_block(&ray_res, decals, x_y_steps);
		if (ray_res.block_x < 0 || ray_res.block_x >= wolf3d->map.width ||
			ray_res.block_y < 0 || ray_res.block_y >= wolf3d->map.height)
		{
			break ;
		}
		ray_res.block = BLOCK_AT(wolf3d, ray_res.block_x, ray_res.block_y);
		if (ray_res.block)
			break ;
	}
	return (render_ray(wolf3d, pixel_x, &ray_res));
}

void	draw_floor_and_ceiling(t_wolf3d *wolf3d)
{
	int		pixel_x;
	int		pixel_y;
	//float	decals[2];
	float	x;
	float	y;
	int		color;

	y = 0;
	while (y < wolf3d->window.height / 2)
	{
		pixel_x = 0;
		while (pixel_x < wolf3d->window.width)
		{
			set_color_at(wolf3d, pixel_x, y, 0x0000ff);
			pixel_x++;
		}
		y++;
	}
	y = 0.0;
	pixel_y = wolf3d->window.height / 2;
	while (pixel_y < wolf3d->window.height)
	{
		x = 0.0;
		pixel_x = 0;
		while (pixel_x < wolf3d->window.width)
		{
			color = fabsf(x - (int)x) < 0.1 || fabsf(y - (int)y) < 0.1 ? 0xffffff : 0x000000;
			set_color_at(wolf3d, pixel_x, pixel_y, color);
			pixel_x++;
			x += 0.03;
		}
		y += 0.03;
		pixel_y++;
	}
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
	float			from[2];

	gettimeofday(&start, NULL);
	if (wolf3d->opts.debug_mode)
		draw_debug_grid(wolf3d);
	else
		draw_floor_and_ceiling(wolf3d);
	from[0] = wolf3d->player.x;
	from[1] = wolf3d->player.y;
	step = wolf3d->opts.big_mode ? 4 : 1;
	x = 0;
	while (x < wolf3d->window.width)
	{
		dir = ((float)x / wolf3d->window.width) * wolf3d->opts.fov;
		dir -= wolf3d->opts.fov / 2;
		send_ray_in_dir(wolf3d, wolf3d->player.looking_dir + dir, x, from);
		x += step;
	}
	if (wolf3d->opts.debug_mode)
		draw_player_on_grid(wolf3d);
	print_time_taken(&start, "Computing took ", "\n");
}

char	init_wolf3d(t_wolf3d *wolf3d, t_value *map_json)
{
	wolf3d->changed = 1;
	gettimeofday(&(wolf3d->last_frame), NULL);
	wolf3d->player.looking_dir = 270.0;
	wolf3d->opts.debug_mode = 0;
	wolf3d->opts.big_mode = 0;
	wolf3d->opts.fov = 60.0;
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
#include <stdio.h>
void	update_values_with_input(t_wolf3d *wolf3d)
{
	float			delta;
	float			decal_x;
	float			decal_y;
	//struct timespec	ts;

	delta = millis_since(&(wolf3d->last_frame));
    /*ts.tv_sec = 0;
    ts.tv_nsec = ((int)(20.0 - delta) % 1000) * 1000000;
    if (ts.tv_nsec > 0)
    {
    	nanosleep(&ts, NULL);
    	delta = millis_since(&(wolf3d->last_frame));
    }*/
	decal_x = cosf(DEG_TO_RAD(wolf3d->player.looking_dir));
	decal_y = sinf(DEG_TO_RAD(wolf3d->player.looking_dir));
	normalize_decals(&decal_x, &decal_y);
	printf("position %f %f\n", wolf3d->player.x, wolf3d->player.y);
	if (wolf3d->window.pressed_keys[0])
	{
		wolf3d->player.x += 5.0 * (delta / 1000.0) * decal_x;
		wolf3d->player.y += 5.0 * (delta / 1000.0) * decal_y;
	}
	if (wolf3d->window.pressed_keys[1])
	{
		wolf3d->player.x -= 5.0 * (delta / 1000.0) * decal_x;
		wolf3d->player.y -= 5.0 * (delta / 1000.0) * decal_y;
	}
	if (wolf3d->window.pressed_keys[2])
	{
		wolf3d->player.x -= 5.0 * (delta / 1000.0) * decal_y;
		wolf3d->player.y += 5.0 * (delta / 1000.0) * decal_x;
	}
	if (wolf3d->window.pressed_keys[3])
	{
		wolf3d->player.x += 5.0 * (delta / 1000.0) * decal_y;
		wolf3d->player.y -= 5.0 * (delta / 1000.0) * decal_x;
	}
	if (wolf3d->window.pressed_keys[4])
		wolf3d->player.looking_dir -= 180.0 * (delta / 1000.0);
	if (wolf3d->window.pressed_keys[5])
		wolf3d->player.looking_dir += 180.0 * (delta / 1000.0);
	if (wolf3d->window.pressed_keys[6])
		wolf3d->opts.fov += 20.0 * (delta / 1000.0);
	if (wolf3d->window.pressed_keys[7])
		wolf3d->opts.fov -= 20.0 * (delta / 1000.0);
	if (wolf3d->opts.fov > 90.0)
		wolf3d->opts.fov = 90.0;
	if (wolf3d->opts.fov < 40.0)
		wolf3d->opts.fov = 40.0;
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
	//clear_screen(wolf3d);
	compute_wolf3d(wolf3d);
	cpy_pixels_to_img(&(wolf3d->window));
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
