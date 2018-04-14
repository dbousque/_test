

#include "wolf3d.h"

void	free_map(t_map *map)
{
	int			i;
	t_texture	*tmp_texture;

	i = 0;
	while (i < map->textures.len)
	{
		tmp_texture = &(((t_texture*)map->textures.elts)[i]);
		if (tmp_texture->name)
			free(tmp_texture->name);
		if (tmp_texture->to_free)
		{
			if (tmp_texture->soil_image)
				SOIL_free_image_data((unsigned char *)tmp_texture->to_free);
			else
				free(tmp_texture->to_free);
		}
		i++;
	}
	free_list(&(map->textures));
	free_list(&(map->blocks));
	free_list(&(map->blocks_positions));
}

void	normalize_decals(float *decal_x, float *decal_y)
{
	float	sum;

	sum = fabsf(*decal_x) + fabsf(*decal_y);
	*decal_x /= sum;
	*decal_y /= sum;
}

int		exit_wolf3d(t_wolf3d *wolf3d)
{
	mlx_destroy_image(wolf3d->window.mlx, wolf3d->window.img);
	mlx_destroy_window(wolf3d->window.mlx, wolf3d->window.win);
	free_map(&(wolf3d->map));
	ft_putstr("Goodbye\n");
	exit(0);
	return (0);
}

void	set_color_at(t_wolf3d *wolf3d, int x, int y, int color)
{
	PIXEL_AT(wolf3d->window, x, y) = color;
	if (wolf3d->opts.big_mode)
	{
		PIXEL_AT(wolf3d->window, x + 1, y) = color;
		PIXEL_AT(wolf3d->window, x, y + 1) = color;
		PIXEL_AT(wolf3d->window, x + 1, y + 1) = color;
	}
}

void	safe_set_color_at(t_wolf3d *w, int x, int y, int color)
{
	if (x >= 0 && x < w->window.width && y >= 0 && y < w->window.height)
		PIXEL_AT(w->window, x, y) = color;
	if (w->opts.big_mode)
	{
		if (x + 1 >= 0 && x + 1 < w->window.width
			&& y >= 0 && y < w->window.height)
		{
			PIXEL_AT(w->window, x + 1, y) = color;
		}
		if (x >= 0 && x < w->window.width
			&& y + 1 >= 0 && y + 1 < w->window.height)
		{
			PIXEL_AT(w->window, x, y + 1) = color;
		}
		if (x + 1 >= 0 && x + 1 < w->window.width
			&& y + 1 >= 0 && y + 1 < w->window.height)
		{
			PIXEL_AT(w->window, x + 1, y + 1) = color;
		}
	}
}