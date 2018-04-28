/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wolf3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:51:59 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 16:52:01 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	init_wolf3d(t_wolf3d *wolf3d, t_value *map_json)
{
	wolf3d->changed = 1;
	gettimeofday(&(wolf3d->last_frame), NULL);
	wolf3d->player.looking_dir = 270.0;
	wolf3d->opts.debug_mode = 0;
	wolf3d->opts.big_mode = 0;
	wolf3d->opts.fov = 75.0;
	wolf3d->opts.hour_of_day = 0.5;
	init_list(&(wolf3d->map.textures), sizeof(t_texture));
	init_list(&(wolf3d->map.blocks), sizeof(t_block));
	init_list(&(wolf3d->map.blocks_positions), sizeof(t_block*));
	return (interpret_map_file(wolf3d, map_json));
}

char	init_wolf3d_win(t_wolf3d *wolf3d, t_config *conf, char *title)
{
	wolf3d->window.antialiasing = conf->antialiasing;
	if (!(init_window(&(wolf3d->window), conf->width, conf->height, title)))
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
