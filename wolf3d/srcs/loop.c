

#include "wolf3d.h"

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
	if (wolf3d->window.pressed_keys[8])
		wolf3d->opts.hour_of_day += 0.2 * (delta / 1000.0);
	if (wolf3d->window.pressed_keys[9])
		wolf3d->opts.hour_of_day -= 0.2 * (delta / 1000.0);
	if (wolf3d->opts.hour_of_day > 0.75)
		wolf3d->opts.hour_of_day = 0.75;
	if (wolf3d->opts.hour_of_day < 0.25)
		wolf3d->opts.hour_of_day = 0.25;
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