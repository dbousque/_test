

#include "fractol.h"

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

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

void	parse_opts(int argc, char **argv, int *width, int *height)
{
	*width = DEFAULT_WIDTH;
	*height = DEFAULT_HEIGHT;
	if (argc > 2)
	{
		*width = parse_uint(argv[2]);
		if (*width == -1 || *width > 4000)
		{
			ft_putstr("Invalid width, setting default value\n");
			*width = DEFAULT_WIDTH;
		}
	}
	if (argc > 3)
	{
		*height = parse_uint(argv[3]);
		if (*height == -1 || *height > 3000)
		{
			ft_putstr("Invalid height, setting default value\n");
			*height = DEFAULT_HEIGHT;
		}
	}
}
