

#include "wolf3d.h"

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

int		influence_color_with_hour(float hour_of_day, int color)
{
	int		r;
	int		g;
	int		b;

	r = (int)*(((unsigned char*)&color) + 2);
	g = (int)*(((unsigned char*)&color) + 1);
	b = (int)*(((unsigned char*)&color) + 0);
	if (hour_of_day > 0.5)
	{
		r = (int)((float)r * (1.0 + (hour_of_day - 0.5)));
		if (r > 255)
			r = 255;
		g = (int)((float)g * (1.0 - (hour_of_day - 0.5)));
		b = (int)((float)b * (1.0 - ((hour_of_day - 0.5) * 2)));
	}
	else
	{
		r = (int)((float)r * (1.0 + ((hour_of_day - 0.5))));
		g = (int)((float)g * (1.0 - ((hour_of_day - 0.5) * 0.2)));
		if (g > 255)
			g = 255;
		b = (int)((float)b * (1.0 - ((hour_of_day - 0.5) * 0.2 )));
		if (b > 255)
			b = 255;
	}
	return (r * 256 * 256 + g * 256 + b);
}

int		attenuate_color(float hour_of_day, t_ray_result *ray_res, int color)
{
	int		r;
	int		g;
	int		b;

	if (!ray_res->block || ray_res->block->is_object)
		return (color);
	color = influence_color_with_hour(hour_of_day, color);
	if (ray_res->face % 2)
		return (color);
	r = (int)*(((unsigned char*)&color) + 2);
	g = (int)*(((unsigned char*)&color) + 1);
	b = (int)*(((unsigned char*)&color) + 0);
	r = (int)((float)r * 0.5);
	g = (int)((float)g * 0.5);
	b = (int)((float)b * 0.5);
	return (r * 256 * 256 + g * 256 + b);
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
		color = attenuate_color(wolf3d->opts.hour_of_day, ray_res, color);
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
	color = influence_color_with_hour(wolf3d->opts.hour_of_day, color);
	set_color_at(wolf3d, p_xy[0], p_xy[1], color);
	tex = wolf3d->map.ceiling;
	color = 0x333333;
	if (tex)
	{
		color = addr_to_c(
			tex, &(tex->pixels[texture_inds[1]]), 0x000000, distance_from_angle
		);
	}
	color = influence_color_with_hour(wolf3d->opts.hour_of_day, color);
	set_color_at(wolf3d, p_xy[0], (wolf3d->window.height - p_xy[1]), color);
}