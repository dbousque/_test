/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:32:53 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 14:32:55 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	apply_image_to_window(t_window *window)
{
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}

void	clear_window(t_window *window)
{
	mlx_clear_window(window->mlx, window->win);
}

char	init_window(t_window *window, int width, int height, char *title)
{
	int		i;

	if (!(window->mlx = mlx_init()))
		return (0);
	if (!(window->win = mlx_new_window(window->mlx, width, height, title)))
		return (0);
	if (!(window->img = mlx_new_image(window->mlx, width, height)))
		return (0);
	if (!(window->pixels = (int*)mlx_get_data_addr(window->img, &i, &i, &i)))
		return (0);
	window->width = width;
	window->height = height;
	window->mouse.x = width / 2;
	window->mouse.y = height / 2;
	i = 0;
	while (i < NB_KEY_PRESS)
	{
		window->pressed_keys[i] = 0;
		i++;
	}
	return (1);
}
