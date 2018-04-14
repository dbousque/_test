

#include "wolf3d.h"

void	init_draw_floor_vars(float floor_xy[2], int pixel_xy[2],
													t_ray_result *rr, int y)
{
	floor_xy[0] = rr->x;
	floor_xy[1] = rr->y;
	pixel_xy[1] = y;
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