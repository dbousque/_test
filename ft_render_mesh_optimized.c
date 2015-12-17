/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_mesh_optimized.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 14:08:39 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/11 14:08:42 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_render_mesh(void *mlx_param)
{
	int			y;
	int			x;
	double		current_x;
	double		current_y;
	t_vector	*dev;
	t_mlx		*mlx;
	double		start_x;
	double		start_y;
	double	min;

	mlx = (t_mlx*)mlx_param;
	//mlx->pov->zoom -= 0.005;
	//mlx->pov->head_balance += 0.7;

	ft_rem_img_from_window(mlx->mlx, mlx->win, mlx->img, 0, 0);

	ft_bzero(mlx->img, WIDTH * HEIGHT * sizeof(int));
	
	min = ft_get_min(mlx);
	dev = ft_new_vector(cos(mlx->pov->head_balance * RAD) * min, sin(mlx->pov->head_balance * RAD) * min);
	ft_get_start_point(&start_x, &start_y, mlx, dev);
	ft_draw_around_mesh(mlx, dev, start_x, start_y, min);
	y = 0;
	while (mlx->mesh[y + 1])
	{
		x = (y % 2 == 0 ? 1 : 2);
		current_x = (x == 1 ? start_x - (y * dev->y_step) : start_x - (y * dev->y_step) + dev->x_step);
		current_y = (x == 1 ? start_y + (y * dev->x_step) : start_y + (y * dev->x_step) + dev->y_step);
		while (x < mlx->mesh[y][0])
		{
			ft_draw_rect(mlx, ft_new_rect(
					ft_new_point(current_x, current_y, mlx->mesh[y][x]),
					ft_new_point(current_x + dev->x_step, current_y + dev->y_step, mlx->mesh[y][x + 1]),
					ft_new_point(current_x + dev->x_step - dev->y_step, current_y + dev->y_step + dev->x_step, mlx->mesh[y + 1][x + 1]),
					ft_new_point(current_x - dev->y_step, current_y + dev->x_step, mlx->mesh[y + 1][x])
										), ft_get_color);
			current_x += dev->x_step * 2;
			current_y += dev->y_step * 2;
			x += 2;
		}
		y++;
	}
	ft_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}
