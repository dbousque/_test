/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 17:32:11 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/17 17:34:02 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		expose_hook(void *mlx_param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)mlx_param;
	ft_render(mlx);
	return (0);
}

int		key_hook3(int keycode, t_mlx *mlx)
{
	if (keycode == F)
	{
		if (mlx->clr_function_num == 0)
		{
			mlx->clr_fct = ft_get_color2;
			mlx->clr_function_num = 1;
		}
		else if (mlx->clr_function_num == 1)
		{
			mlx->clr_fct = ft_get_color3;
			mlx->clr_function_num = 2;
		}
		else if (mlx->clr_function_num == 2)
		{
			mlx->clr_fct = ft_get_color4;
			mlx->clr_function_num = 3;
		}
		else
		{
			mlx->clr_fct = ft_get_color;
			mlx->clr_function_num = 0;
		}
	}
	ft_render(mlx);
	return (0);
}

int		key_hook2(int keycode, t_mlx *mlx)
{
	if (keycode == UP)
		mlx->center->y += 30.0;
	else if (keycode == DOWN)
		mlx->center->y -= 30.0;
	else if (keycode == M)
	{
		if (mlx->view_mode == 0)
		{
			mlx->view_mode = 1;
			mlx->angle = 30.0;
		}
		else
			mlx->view_mode = 0;
	}
	else if (keycode == H)
		mlx->height_factor /= 1.1;
	else if (keycode == J)
		mlx->height_factor *= 1.1;
	else if (keycode == ESC)
		return (ft_exit(mlx));
	else
		return (key_hook3(keycode, mlx));
	ft_render(mlx);
	return (0);
}

int		key_hook(int keycode, void *mlx_param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)mlx_param;
	if (keycode == Z)
		mlx->unit *= 1.1;
	else if (keycode == X)
		mlx->unit /= 1.1;
	else if (keycode == LEFT)
		mlx->center->x += 30.0;
	else if (keycode == RIGHT)
		mlx->center->x -= 30.0;
	else if (keycode == W && mlx->elevation < 1.0)
		mlx->elevation += 0.03;
	else if (keycode == S && mlx->elevation > -1.0)
		mlx->elevation -= 0.03;
	else if (keycode == A && mlx->view_mode == 0)
		mlx->angle += 1.0;
	else if (keycode == D && mlx->view_mode == 0)
		mlx->angle -= 1.0;
	else
		return (key_hook2(keycode, mlx));
	ft_render(mlx);
	return (0);
}
