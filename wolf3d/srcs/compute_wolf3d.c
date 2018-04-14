

#include "wolf3d.h"

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
	advance_by += 0.001;
	ray_res->x += decals[0] * advance_by;
	ray_res->y += decals[1] * advance_by;
	ray_res->block_x = floorf(ray_res->x);
	ray_res->block_y = floorf(ray_res->y);
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