

#include "wolf3d.h"

void	render_debug_ray(t_wolf3d *wolf3d, int pixel_x, t_ray_result *ray_res)
{
	int		start_x;
	int		start_y;
	int		from[2];
	int		to[2];
	int		block_size;

	if (pixel_x % 40 != 0)
		return ;
	block_size = wolf3d->opts.debug_block_size;
	start_x = wolf3d->window.width - (wolf3d->map.width * block_size);
	start_x /= 2;
	start_y = wolf3d->window.height - (wolf3d->map.height * block_size);
	start_y /= 2;
	from[0] = start_x + (wolf3d->player.x * block_size);
	from[1] = start_y + (wolf3d->player.y * block_size);
	to[0] = start_x + (int)(ray_res->x * (float)block_size);
	to[1] = start_y + (int)(ray_res->y * (float)block_size);
	safe_draw_line(wolf3d, from, to, ray_res->block ? 0x156aef : 0x8db3ef);
}

void	draw_debug_column(t_wolf3d *wolf3d, int x, int start_x_y[2],
																int block_size)
{
	int		y;
	int		color;
	int		from[2];

	y = 0;
	while (y < wolf3d->map.height)
	{
		color = 0x444444;
		if (BLOCK_AT(wolf3d, x, y))
			color = 0xf2df4d;
		from[0] = start_x_y[0] + x * block_size;
		from[1] = start_x_y[1] + y * block_size;
		draw_square(wolf3d, from, block_size, color);
		y++;
	}
}

void	draw_player_on_grid(t_wolf3d *wolf3d)
{
	int		player_x;
	int		player_y;
	int		start_x_y[2];
	int		block_size;

	block_size = wolf3d->opts.debug_block_size;
	start_x_y[0] = wolf3d->window.width - (wolf3d->map.width * block_size);
	start_x_y[0] /= 2;
	start_x_y[1] = wolf3d->window.height - (wolf3d->map.height * block_size);
	start_x_y[1] /= 2;
	player_x = start_x_y[0] + (wolf3d->player.x * block_size);
	player_y = start_x_y[1] + (wolf3d->player.y * block_size);
	safe_set_color_at(wolf3d, player_x, player_y, 0xef1414);
	safe_set_color_at(wolf3d, player_x, player_y + 1, 0xef1414);
	safe_set_color_at(wolf3d, player_x, player_y - 1, 0xef1414);
	safe_set_color_at(wolf3d, player_x - 1, player_y, 0xef1414);
	safe_set_color_at(wolf3d, player_x - 1, player_y + 1, 0xef1414);
	safe_set_color_at(wolf3d, player_x - 1, player_y - 1, 0xef1414);
	safe_set_color_at(wolf3d, player_x + 1, player_y, 0xef1414);
	safe_set_color_at(wolf3d, player_x + 1, player_y + 1, 0xef1414);
	safe_set_color_at(wolf3d, player_x + 1, player_y - 1, 0xef1414);
}

void	draw_debug_grid(t_wolf3d *wolf3d)
{
	int		block_size;
	int		start_x_y[2];
	int		x;	

	clear_screen(wolf3d);
	block_size = (float)wolf3d->window.width / (float)wolf3d->map.width;
	if (block_size > (float)wolf3d->window.height / (float)wolf3d->map.height)
		block_size = (float)wolf3d->window.height / (float)wolf3d->map.height;
	block_size = (int)((float)block_size * 0.8);
	wolf3d->opts.debug_block_size = block_size;
	start_x_y[0] = wolf3d->window.width - (wolf3d->map.width * block_size);
	start_x_y[0] /= 2;
	start_x_y[1] = wolf3d->window.height - (wolf3d->map.height * block_size);
	start_x_y[1] /= 2;
	x = 0;
	while (x < wolf3d->map.width)
	{
		draw_debug_column(wolf3d, x, start_x_y, block_size);
		x++;
	}
}