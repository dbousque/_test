/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_full.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 12:45:38 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/11 12:46:13 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_draw_full_triangle(t_mlx *mlx, t_point *p1, t_point *p2, t_point *p3)
{
	double	x_step1;
	double	y_step1;
	double	x_step2;
	double	y_step2;
	int		nb_steps[2];



	t_point	*tmp1;
	t_point	*tmp2;
	int		max_steps;

	ft_get_steps(p2, p1, &x_step1, &y_step1);
	ft_get_steps(p2, p3, &x_step2, &y_step2);
	if (ft_real_value(x_step1) > ft_real_value(y_step1))
		nb_steps[0] = (int)(ft_real_value(p1->x - p2->x)) + 1;
	else
		nb_steps[0] = (int)(ft_real_value(p1->y - p2->y)) + 1;
	if (ft_real_value(x_step2) > ft_real_value(y_step2))
		nb_steps[1] = (int)(ft_real_value(p3->x - p2->x)) + 1;
	else
		nb_steps[1] = (int)(ft_real_value(p3->y - p2->y)) + 1;
	if (nb_steps[0] > nb_steps[1])
	{
		x_step2 /= (((double)(nb_steps[0])) / nb_steps[1]);
		y_step2 /= (((double)(nb_steps[0])) / nb_steps[1]);
		max_steps = nb_steps[0];
	}
	else
	{
		x_step1 /= (((double)(nb_steps[1])) / nb_steps[0]);
		y_step1 /= (((double)(nb_steps[1])) / nb_steps[0]);
		max_steps = nb_steps[1];
	}
	tmp1 = ft_new_point(p2->x, p2->y, p2->height);
	tmp2 = ft_new_point(p2->x, p2->y, p2->height);
	ft_draw_line(mlx, p1, p2, ft_get_color);
	ft_draw_line(mlx, p2, p3, ft_get_color);
	ft_draw_line(mlx, p1, p3, ft_get_color);
	while (max_steps >= 0)
	{
		ft_draw_line(mlx, tmp1, tmp2, ft_get_color);
		tmp1->x += x_step1;
		tmp1->y += y_step1;
		tmp2->x += x_step2;
		tmp2->y += y_step2;
		max_steps--;
	}
}

void	ft_draw_full_rect(t_mlx *mlx, t_rect *rect,
			int (*ft_clr) (t_point *p1, t_point *p2, double perc))
{
	(void)ft_clr;
	ft_draw_full_triangle(mlx, rect->points[0], rect->points[1], rect->points[2]);
	ft_draw_full_triangle(mlx, rect->points[0], rect->points[3], rect->points[2]);
}
