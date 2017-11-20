

#include "fractol.h"

int		main(int argc, char **argv)
{
	t_window	window;
	int			width;
	int			height;

	parse_opts(argc, argv, &width, &height);
	if (!init_window(&window, width, height, "Helloz"))
	{
		ft_putstr("Could not initialize window\n");
		return (1);
	}
	mlx_loop(window.mlx);
	return (0);
}
