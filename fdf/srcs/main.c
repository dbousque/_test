/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 14:33:05 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/17 17:35:06 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_putintint(int **mesh)
{
	int		i;
	int		x;

	i = 0;
	while (mesh[i])
	{
		x = 0;
		while (x <= mesh[i][0])
		{
			ft_putnbr(mesh[i][x]);
			ft_putchar('.');
			x++;
		}
		ft_putchar('\n');
		i++;
	}
}

double	get_unit(t_mlx *mlx)
{
	double	tmp;

	tmp = ((double)mlx->width) / ft_nb_lines(mlx->mesh);
	if (tmp > ((double)mlx->height) / mlx->mesh[0][0])
		return (((double)mlx->height) / mlx->mesh[0][0]);
	return (tmp);
}

int		main(int argc, char **argv)
{
	t_mlx	*mlx;
	int		**mesh;

	if (argc == 2)
	{
		if (!(mesh = ft_get_mesh(argv[1])))
			return (ft_map_error());
		if (!(mlx = ft_new_mlx(WIDTH, HEIGHT, "fdf")))
			return (ft_connection_failed());
		mlx->mesh = mesh;
		mlx->higher_point = mlx->mesh[0][1];
		mlx->lower_point = mlx->mesh[0][1];
		if (!(mlx->points = empty_points(mlx)))
			return (ft_unexpected_error());
		mlx->unit = get_unit(mlx);
		ft_render((void*)mlx);
		mlx_expose_hook(mlx->win, expose_hook, mlx);
		mlx_hook(mlx->win, 2, 3, key_hook, (void*)mlx);
		mlx_mouse_hook(mlx->win, mouse_hook, (void*)mlx);
		mlx_loop(mlx->mlx);
	}
	return (0);
}
