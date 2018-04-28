/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:32:31 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 14:32:33 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		exit_fractol(t_fractol *fractol)
{
	mlx_destroy_image(fractol->window.mlx, fractol->window.img);
	mlx_destroy_window(fractol->window.mlx, fractol->window.win);
	ft_putstr("bye\n");
	exit(0);
	return (0);
}

int		parse_uint(char *str)
{
	int		res;
	int		i;

	i = 0;
	res = 0;
	if (!str[0] || str[0] == '0')
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

char	valid_fractal(int argc, char **argv)
{
	(void)argc;
	if (ft_streq(argv[1], "mandelbrot"))
		return (1);
	else if (ft_streq(argv[1], "julia"))
		return (1);
	else if (ft_streq(argv[1], "ship"))
		return (1);
	else if (ft_streq(argv[1], "sierpinski"))
		return (1);
	else if (ft_streq(argv[1], "tree"))
		return (1);
	else if (ft_streq(argv[1], "snowflake"))
		return (1);
	else if (ft_streq(argv[1], "losange"))
		return (1);
	else if (ft_streq(argv[1], "dragon"))
		return (1);
	return (0);
}

char	print_usage(void)
{
	ft_putstr("Please provide a valid fractal name as argument. One of :");
	ft_putstr(" [mandelbrot,julia,ship,sierpinski,tree,snowflake,");
	ft_putstr("losange,dragon]\n\n");
	ft_putstr("Usage : ./fractal <fractal_name> [width] [height]\n\n");
	ft_putstr(".                 decr iterations\n");
	ft_putstr("/                 incr iterations\n");
	ft_putstr("F                 change fractal\n");
	ft_putstr("P                 change color palette\n");
	ft_putstr("ARROW KEYS        move around\n");
	ft_putstr("+/-               zoom\n");
	ft_putstr("MOUSE WHEEL       zoom\n");
	ft_putstr("B                 big mode\n");
	ft_putstr("M                 freeze julia\n");
	ft_putstr("X/Z               arg1 input\n");
	ft_putstr("ESC               exit\n");
	return (0);
}

char	parse_opts(int argc, char **argv, int *width, int *height)
{
	*width = DEFAULT_WIDTH;
	*height = DEFAULT_HEIGHT;
	if (argc <= 1 || !valid_fractal(argc, argv))
		return (print_usage());
	if (argc > 2)
	{
		*width = parse_uint(argv[2]);
		if (*width == -1 || *width < 100 || *width > 4000)
		{
			ft_putstr("Invalid width, setting default value\n");
			*width = DEFAULT_WIDTH;
		}
	}
	if (argc > 3)
	{
		*height = parse_uint(argv[3]);
		if (*height == -1 || *height < 100 || *height > 3000)
		{
			ft_putstr("Invalid height, setting default value\n");
			*height = DEFAULT_HEIGHT;
		}
	}
	return (1);
}
