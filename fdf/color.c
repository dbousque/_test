/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 17:39:03 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/14 17:39:22 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_get_color(t_mlx *mlx, t_point *p1, t_point *p2, double percentage)
{
	double	height;
	int		green;

	(void)mlx;
	height = p1->height + ((p2->height - p1->height) * percentage / 100.0);
	green = 0x0000CC - height * 10;
	return (0xCC00CC + green * 256);
}

int		rgb_to_color(unsigned char r, unsigned char g, unsigned int b)
{
	return (r * 256 * 256 + g * 256 + b);
}

int		ft_get_color2(t_mlx *mlx, t_point *p1, t_point *p2, double percentage)
{
	double	height;
	int		res;

	(void)mlx;
	height = p1->height + ((p2->height - p1->height) * percentage / 100.0);
	res = rgb_to_color(50 + height * 20, 50 + height * 20, 50 + height * 20);
	return (res);
}

int		ft_get_color3(t_mlx *mlx, t_point *p1, t_point *p2, double percentage)
{
	double	height;

	(void)mlx;
	height = p1->height + ((p2->height - p1->height) * percentage / 100.0);
	if (height <= 0.0)
		return (0x0000FF - (mlx->lower_point > -1.0 ? 0.0 : height / mlx->lower_point * 200));
	else if (height < mlx->higher_point / 8)
		return (rgb_to_color(0, 70 + height / mlx->higher_point * 1000, 35));
	else if (height < mlx->higher_point / 1.8)
		return (rgb_to_color(230 - height / mlx->higher_point * 300 , 65, 45));
	else
		return (rgb_to_color(230 * height / mlx->higher_point * 1.3, 230 * height / mlx->higher_point * 1.3, 230 * height / mlx->higher_point * 1.3));
	return (0x999999);
}
