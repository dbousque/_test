/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 14:33:05 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/17 14:30:03 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define W 13
#define A 0
#define S 1
#define D 2
#define H 4
#define J 38
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

int		key_hook3(int keycode, t_mlx *mlx)
{
	if (keycode == F)
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
		else if (mlx->clr_function_num == 2)
		{
			mlx->color_function = ft_get_color4;
			mlx->clr_function_num = 3;
		}
		else
		{
			mlx->color_function = ft_get_color;
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

void	make_point_higher(t_mlx *mlx, int ind_y, int ind_x)
{
	if (mlx->higher_point - mlx->lower_point < 10)
	{
		mlx->mesh[ind_y][ind_x + 1] = mlx->mesh[ind_y][ind_x + 1] + 1;
		mlx->higher_point += 1;
	}
	else
		mlx->mesh[ind_y][ind_x + 1] += (mlx->higher_point
												- mlx->lower_point) / 10;
	if (mlx->mesh[ind_y][ind_x + 1] > mlx->higher_point)
		mlx->higher_point = mlx->mesh[ind_y][ind_x + 1];
}

void	update_point(t_mlx *mlx, int ind_y, int ind_x, int keycode)
{
	if (keycode == 1)
		make_point_higher(mlx, ind_y, ind_x);
	else
	{
		if (mlx->higher_point - mlx->lower_point < 10)
		{
			mlx->mesh[ind_y][ind_x + 1] = mlx->mesh[ind_y][ind_x + 1] - 1;
			mlx->lower_point -= 1;
		}
		else
			mlx->mesh[ind_y][ind_x + 1] -= (mlx->higher_point
												- mlx->lower_point) / 10;
		if (mlx->mesh[ind_y][ind_x + 1] < mlx->lower_point)
			mlx->lower_point = mlx->mesh[ind_y][ind_x + 1];
	}
	ft_render(mlx);
}

int		mouse_hook(int keycode, int x, int y, t_mlx *mlx)
{
	int		i[2];
	double	score;
	int		ind[2];

	score = -1.0;
	i[0] = 0;
	while (mlx->points[i[0]])
	{
		i[1] = 0;
		while (mlx->points[i[0]][i[1]])
		{
			if (score == -1.0 || ft_real_value(mlx->points[i[0]][i[1]]->x - x)
					+ ft_real_value(mlx->points[i[0]][i[1]]->y - y) < score)
			{
				score = ft_real_value(mlx->points[i[0]][i[1]]->x - x)
					+ ft_real_value(mlx->points[i[0]][i[1]]->y - y);
				ind[0] = i[0];
				ind[1] = i[1];
			}
			i[1]++;
		}
		i[0]++;
	}
	update_point(mlx, ind[0], ind[1], keycode);
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
		if (!(mlx = ft_new_mlx(WIDTH, HEIGHT, "fdf")))
			return (ft_connection_failed());
		mlx->mesh = mesh;
		mlx->higher_point = mlx->mesh[0][1];
		mlx->lower_point = mlx->mesh[0][1];
		if (!(mlx->points = empty_points(mlx)))
			return (ft_unexpected_error());
		mlx->unit = get_unit(mlx);
		ft_render((void*)mlx);
		//mlx_expose_hook(mlx->win, expose_hook, mlx);
		mlx_hook(mlx->win, 2, 3, key_hook, (void*)mlx);
		mlx_mouse_hook(mlx->win, mouse_hook, (void*)mlx);
		mlx_loop(mlx->mlx);
	}
	return (0);
}
