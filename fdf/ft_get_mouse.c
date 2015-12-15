/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 11:26:38 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/15 17:48:41 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_get_mouse(int x, int y, void *mlx_param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)mlx_param;
	(void)y;
	//(void)button;
	if (x == 4)
	{
		ft_putendl("LOL");
		mlx->unit += 0.1;
		ft_putendl("LOL2");
	}
	ft_putnbr(x);
	ft_putchar('\n');
	return (0);
}
