/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 11:26:38 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/11 11:55:25 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_get_mouse(int x, int y, t_mlx *mlx)
{
	(void)y;
	(void)mlx;
	//(void)button;
	if (x == 4)
	{
		mlx->pov->zoom += 0.1;
	}
	ft_putnbr(x);
	ft_putchar('\n');
	return (0);
}