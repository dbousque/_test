

#include "wolf3d.h"

void	render_wolf3d(t_wolf3d *wolf3d)
{
	apply_image_to_window(&(wolf3d->window));
}

int		addr_to_c(t_texture *texture, unsigned char *addr, int ori,
													float distance_from_angle)
{
	float	ratio;
	float	bright;
	int		res;

	ratio = 0.0;
	bright = 0.4 + (distance_from_angle * 10);
	bright = fminf(bright, 1.0);
	res = 0;
	if (texture->pixel_width == 4)
	{
		ratio = ((float)*(addr + 3)) / 256.0;
		ratio = 1.0 - ratio;
		res = (int)(((float)*(((unsigned char*)&ori) + 2)) * ratio * bright);
		res *= 256;
		res += (int)(((float)*(((unsigned char*)&ori) + 1)) * ratio * bright);
		res *= 256;
		res += (int)(((float)*(((unsigned char*)&ori) + 0)) * ratio * bright);
	}
	res += (int)(((float)*(addr + 2)) * (1.0 - ratio) * bright) * 256 * 256;
	res += (int)(((float)*(addr + 1)) * (1.0 - ratio) * bright) * 256;
	res += (int)(((float)*(addr + 0)) * (1.0 - ratio) * bright);
	return (res);
}

float	make_distance(int i, int block_until)
{
	float	part1;
	float	part2;

	part1 = (float)i / (block_until * 2);
	part2 = 1.015 - ((float)i / (block_until * 2));
	return (fminf(part1, part2));
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
	text = ray_res->block->obj_texture;
	if (!ray_res->block->is_object)
		text = ray_res->block->faces[ray_res->face];
	is[0] = (int)(ray_res->decal_in_face * (float)text->width);
	is[0] *= text->pixel_width;
	i = start_y < 0 ? -start_y : 0;
	while (i < block_until * 2 && start_y + i < wolf3d->window.height)
	{
		is[1] = ((float)i / (block_until * 2)) * text->height;
		is[1] *= text->pixel_width;
		color = addr_to_c(text, &(text->pixels[is[0] + is[1] * text->width]),
			PIXEL_AT(wolf3d->window, pixel_x, start_y + i),
			ray_res->block->is_object ? 1.0 : make_distance(i, block_until)
		);
		set_color_at(wolf3d, pixel_x, start_y + i, color);
		i++;
	}
}

void	draw_floor_and_ceiling_from_coords(t_wolf3d *wolf3d, int p_xy[2],
								float distance_from_angle, int texture_inds[2])
{
	int			color;
	t_texture	*tex;

	tex = wolf3d->map.floor;
	color = 0x333333;
	if (tex)
	{
		color = addr_to_c(
			tex, &(tex->pixels[texture_inds[0]]), 0x000000,
			distance_from_angle + 0.02
		);
	}
	set_color_at(wolf3d, p_xy[0], p_xy[1], color);
	tex = wolf3d->map.ceiling;
	color = 0x333333;
	if (tex)
	{
		color = addr_to_c(
			tex, &(tex->pixels[texture_inds[1]]), 0x000000, distance_from_angle
		);
	}
	set_color_at(wolf3d, p_xy[0], (wolf3d->window.height - p_xy[1]), color);
}

float	get_distance_from_angle(t_wolf3d *wolf3d, int y, int start_y,
													t_ray_result *ray_res)
{
	float	distance_from_angle;

	distance_from_angle = fminf(
		(float)(y - start_y) / (wolf3d->window.height - start_y), 
		1.015 - ((float)(y - start_y) / (wolf3d->window.height - start_y)));
	distance_from_angle = distance_from_angle * ray_res->distance / 3.0;
	return (distance_from_angle);
}

void	get_texture_inds(t_wolf3d *wolf3d, float text_x, float text_y,
														int texture_inds[2])
{
	t_texture	*tex;

	tex = wolf3d->map.floor;
	if (tex)
	{
		texture_inds[0] =
			(int)(text_x * tex->width) * tex->pixel_width +
			(int)(text_y * tex->height) * tex->width * tex->pixel_width;
	}
	tex = wolf3d->map.ceiling;
	if (tex)
	{
		texture_inds[1] =
			(int)(text_x * tex->width) * tex->pixel_width +
			(int)(text_y * tex->height) * tex->width * tex->pixel_width;
	}
}

void	calc_text_xy(t_wolf3d *wolf3d, float hw[2], float floor_xy[2],
															float text_xy[2])
{
	text_xy[0] = hw[1] * floor_xy[0] + (0.7 - hw[1]) * wolf3d->player.x;
    text_xy[1] = hw[1] * floor_xy[1] + (0.7 - hw[1]) * wolf3d->player.y;
    text_xy[0] -= (int)text_xy[0];
    text_xy[1] -= (int)text_xy[1];
}

void	init_draw_floor_vars(float floor_xy[2], int pixel_xy[2],
													t_ray_result *rr, int y)
{
	floor_xy[0] = rr->x;
	floor_xy[1] = rr->y;
	pixel_xy[1] = y;
}

void	draw_floor_and_ceiling(t_wolf3d *wolf3d, t_ray_result *rr,
														int pixel_x, int y)
{
	int		tex_inds_st_y[3];
	int		pixel_xy[2];
	float	t_xy[2];
	float	floor_xy[2];
	float	hw[2];

	hw[0] = wolf3d->window.height;
	tex_inds_st_y[2] = y;
	pixel_xy[0] = pixel_x;
	init_draw_floor_vars(floor_xy, pixel_xy, rr, y);
	while (pixel_xy[1] < wolf3d->window.height)
	{
        hw[1] = (hw[0] / (pixel_xy[1] * 2.0 - hw[0] + 0.0001)) / rr->distance;
        calc_text_xy(wolf3d, hw, floor_xy, t_xy);
        if (t_xy[0] < 0.0 || t_xy[1] < 0.0 || t_xy[0] >= 1.0 || t_xy[1] >= 1.0)
        {
        	pixel_xy[1]++;
        	continue ;
        }
        get_texture_inds(wolf3d, t_xy[0], t_xy[1], tex_inds_st_y);
        draw_floor_and_ceiling_from_coords(wolf3d, pixel_xy, 
        	get_distance_from_angle(wolf3d, pixel_xy[1], tex_inds_st_y[2], rr),
        	tex_inds_st_y);
		pixel_xy[1]++;
	}
}

void	draw_black_column(t_wolf3d *wolf3d, int pixel_x, int block_until)
{
	int		i;
	int		start_y;

	start_y = wolf3d->window.height / 2 - block_until;
	i = start_y < 0 ? -start_y : 0;
	while (i < block_until * 2 && start_y + i < wolf3d->window.height)
	{
		set_color_at(wolf3d, pixel_x, start_y + i, 0x000000);
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

	height_at_zero = 1.3;
	full_screen_point = 1.0;
	block_height = height_at_zero / (ray_res->distance / full_screen_point);
	block_until = (wolf3d->window.height / 2) * block_height;
	if (ray_res->block)
		draw_texture(wolf3d, pixel_x, ray_res, block_until);
	else
		draw_black_column(wolf3d, pixel_x, block_until);
	y = wolf3d->window.height / 2 + block_until;
	draw_floor_and_ceiling(wolf3d, ray_res, pixel_x, y);
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

	height_at_zero = 1.3;
	full_screen_point = 1.0;
	block_height = height_at_zero / (ray_res->distance / full_screen_point);
	block_until = (wolf3d->window.height / 2) * block_height;
	from[0] = ray_res->x;
	from[1] = ray_res->y;
	write(1, "sa\n", 3);
	send_ray_in_dir(wolf3d, ray_res->direction, pixel_x, from);
	write(1, "dt\n", 3);
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
	write(1, "do\n", 3);
	draw_object(wolf3d, pixel_x, ray_res);
}

void	render_ray(t_wolf3d *wolf3d, int pixel_x, t_ray_result *ray_res)
{
	if (wolf3d->opts.debug_mode)
		return (render_debug_ray(wolf3d, pixel_x, ray_res));
	write(1, "rra\n", 4);
	if (ray_res->block && ray_res->block->is_object)
		write(1, "iso\n", 4);
	if (ray_res->block && ray_res->block->is_object)
		return (render_object(wolf3d, pixel_x, ray_res));
	ray_res->distance =
	fabsf(wolf3d->player.x - ray_res->x) *
		fabsf(wolf3d->player.x - ray_res->x) +
	fabsf(wolf3d->player.y - ray_res->y) *
		fabsf(wolf3d->player.y - ray_res->y);
	ray_res->distance = sqrtf(ray_res->distance);
	if (ray_res->block)
	{
		if (ray_res->face == 0)
			ray_res->decal_in_face = ((int)ray_res->x + 1) - ray_res->x;
		else if (ray_res->face == 1)
			ray_res->decal_in_face = ((int)ray_res->y + 1) - ray_res->y;
		else if (ray_res->face == 2)
			ray_res->decal_in_face = ray_res->x - (int)ray_res->x;
		else
			ray_res->decal_in_face = ray_res->y - (int)ray_res->y;
	}
	write(1, "dc\n", 3);
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
	ray_res->block_x = floorf(ray_res->x);
	ray_res->block_y = floorf(ray_res->y);
}
#include <stdio.h>
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
	write(1, "sri\n", 4);
	fflush(stdout);
	decals[0] = cosf(DEG_TO_RAD(direction));
	decals[1] = sinf(DEG_TO_RAD(direction));
	write(1, "decals\n", 7);
	fflush(stdout);
	normalize_decals(&(decals[0]), &(decals[1]));
	write(1, "norm\n", 5);
	fflush(stdout);
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
	write(1, "rer\n", 4);
	return (render_ray(wolf3d, pixel_x, &ray_res));
}

void	*compute_wolf3d_part(void *thread_data)
{
	t_wolf3d	*wolf3d;
	int			x;
	int			step;
	float		dir;
	float		from[2];

	wolf3d = ((t_thread_data*)thread_data)->wolf3d;
	x = ((t_thread_data*)thread_data)->from_x;
	from[0] = wolf3d->player.x;
	from[1] = wolf3d->player.y;
	step = wolf3d->opts.big_mode ? 4 : 1;
	while (x < ((t_thread_data*)thread_data)->until_x)
	{
		dir = ((float)x / wolf3d->window.width) * wolf3d->opts.fov;
		dir -= wolf3d->opts.fov / 2;
		write(1, "dir\n", 4);
		send_ray_in_dir(wolf3d, wolf3d->player.looking_dir + dir, x, from);
		x += step;
	}
	return (NULL);
}

void	compute_wolf3d(t_wolf3d *wolf3d)
{
	t_thread_data	data[NB_THREADS];
	pthread_t		threads[NB_THREADS];
	int				i;
	struct timeval	start;

	gettimeofday(&start, NULL);
	if (wolf3d->opts.debug_mode)
		draw_debug_grid(wolf3d);
	i = 0;
	while (i < NB_THREADS)
	{
		data[i].wolf3d = wolf3d;
		data[i].from_x = i * (wolf3d->window.width / NB_THREADS);
		data[i].until_x = (i + 1) * (wolf3d->window.width / NB_THREADS);
		if (i == NB_THREADS - 1)
			data[i].until_x = wolf3d->window.width;
		launch_thread(threads, data, i);
		i++;
	}
	wait_for_threads_to_finish(threads);
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
	wolf3d->opts.fov = 75.0;
	init_list(&(wolf3d->map.textures), sizeof(t_texture));
	init_list(&(wolf3d->map.blocks), sizeof(t_block));
	init_list(&(wolf3d->map.blocks_positions), sizeof(t_block*));
	return (interpret_map_file(wolf3d, map_json));
}

char	init_wolf3d_win(t_wolf3d *wolf3d, int width, int height, char *title)
{
	wolf3d->window.antialiasing = 0;
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

char	player_position_allowed(t_wolf3d *wolf3d)
{
	t_block		*block;

	if (wolf3d->player.x < 0.0 || wolf3d->player.y < 0.0)
		return (0);
	if (wolf3d->player.x >= wolf3d->map.width)
		return (0);
	if (wolf3d->player.y >= wolf3d->map.height)
		return (0);
	block = BLOCK_AT(wolf3d, (int)wolf3d->player.x, (int)wolf3d->player.y);
	if (!block || block->go_through)
		return (1);
	return (0);
}

void	move_player_to_endpoint(t_wolf3d *wolf3d, float delta, float decal_x,
																float decal_y)
{
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
}

void	move_player(t_wolf3d *wolf3d, float delta)
{
	float	decal_x;
	float	decal_y;
	float	old_x;
	float	old_y;

	old_x = wolf3d->player.x;
	old_y = wolf3d->player.y;
	decal_x = cosf(DEG_TO_RAD(wolf3d->player.looking_dir));
	decal_y = sinf(DEG_TO_RAD(wolf3d->player.looking_dir));
	normalize_decals(&decal_x, &decal_y);
	move_player_to_endpoint(wolf3d, delta, decal_x, decal_y);
	if (!player_position_allowed(wolf3d))
	{
		wolf3d->player.x = old_x;
		wolf3d->player.y = old_y;
	}
}

void	update_values_with_input(t_wolf3d *wolf3d)
{
	float	delta;

	delta = millis_since(&(wolf3d->last_frame));
	move_player(wolf3d, delta);

	if (wolf3d->window.pressed_keys[4])
		wolf3d->player.looking_dir -= 180.0 * (delta / 1000.0);
	if (wolf3d->window.pressed_keys[5])
		wolf3d->player.looking_dir += 180.0 * (delta / 1000.0);
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
