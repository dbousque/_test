/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 14:33:05 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/15 19:03:55 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define W 13
#define A 0
#define S 1
#define D 2
#define LEFT 123
#define UP 126
#define DOWN 125
#define RIGHT 124
#define Z 6
#define X 7
#define M 46
#define F 3
#define SPACE 49

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

int		expose_hook(t_mlx *mlx)
{
	(void)mlx;
	//ft_render(mlx);
	return (0);
}

int		key_hook(int keycode, void *mlx_param)
{
	t_mlx	*mlx;
	

	mlx = (t_mlx*)mlx_param;
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == SPACE)
		mlx->keycode = -1;
	else if (keycode == Z)
		mlx->unit *= 1.1;
	else if (keycode == X)
		mlx->unit /= 1.1;
	else if (keycode == LEFT)
		mlx->center->x += 10.0;
	else if (keycode == RIGHT)
		mlx->center->x -= 10.0;
	else if (keycode == F)
	{
		if (mlx->clr_function_num == 0)
		{
			mlx->color_function = ft_get_color2;
			mlx->clr_function_num = 1;
		}
		else if (mlx->clr_function_num == 1)
		{
			mlx->color_function = ft_get_color3;
			mlx->clr_function_num = 2;
		}
		else
		{
			mlx->color_function = ft_get_color;
			mlx->clr_function_num = 0;
		}
	}
	else if (keycode == UP)
		mlx->center->y += 10.0;
	else if (keycode == DOWN)
		mlx->center->y -= 10.0;
	else if (keycode == W && mlx->elevation < 1.0)
		mlx->elevation += 0.05;
	else if (keycode == S && mlx->elevation > -1.0)
		mlx->elevation -= 0.05;
	else if (keycode == A && mlx->view_mode == 0)
		mlx->angle += 1.0;
	else if (keycode == D && mlx->view_mode == 0)
		mlx->angle -= 1.0;
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
	mlx->keycode = keycode;
	ft_render(mlx);
	return (0);
}

int		main(int argc, char **argv)
{
	t_mlx	*mlx;
	int		**mesh;

	if (argc == 2)
	{
		if (!(mesh = ft_get_mesh(argv[1])))
			return (ft_map_error());
		//ft_putintint(mesh);
		if (!(mlx = ft_new_mlx(WIDTH, HEIGHT, "fdf")))
			return (ft_connection_failed());
		mlx->mesh = mesh;
		if (!(mlx->points = empty_points(mlx)))
			return (ft_unexpected_error());
		mlx->unit = get_unit(mlx);
		ft_render((void*)mlx);
		mlx_expose_hook(mlx->win, expose_hook, mlx);
		mlx_key_hook(mlx->win, key_hook, (void*)mlx);
		mlx_loop(mlx->mlx);
	}
	return (0);
}
