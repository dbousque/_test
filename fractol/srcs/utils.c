

#include "fractol.h"

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

int		exit_fractol(t_window *window)
{
	mlx_destroy_image(window->mlx, window->img);
	mlx_destroy_window(window->mlx, window->win);
	ft_putstr("bye\n");
	exit(0);
	return (0);
}

int		parse_int(char *str)
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
	if (argc > 1)
	{
		*width = parse_int(argv[1]);
		if (*width == -1 || *width > 4000)
		{
			ft_putstr("Invalid width, setting default value\n");
			*width = DEFAULT_WIDTH;
		}
	}
	if (argc > 2)
	{
		*height = parse_int(argv[2]);
		if (*height == -1 || *height > 3000)
		{
			ft_putstr("Invalid height, setting default value\n");
			*height = DEFAULT_HEIGHT;
		}
	}
}
