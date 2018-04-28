/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palettes2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:51:34 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 14:51:36 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_greyscale_palette(int *palette)
{
	int		i;
	int		x;

	i = 0;
	while (i < PALETTE_LEN)
	{
		x = (256 / (PALETTE_LEN - 1)) * i;
		palette[i] = (x * 256 * 256) + (x * 256) + x;
		i++;
	}
}

void	init_bluescale_palette(int *palette)
{
	int		i;
	int		b;

	i = 0;
	while (i < PALETTE_LEN)
	{
		b = (200 / (PALETTE_LEN - 1)) * i + 41;
		palette[i] = 0x0c0000 + 0x000600 + b;
		i++;
	}
}
