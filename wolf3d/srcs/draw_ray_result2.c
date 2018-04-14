

#include "wolf3d.h"

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