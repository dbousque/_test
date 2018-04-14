

#include "wolf3d.h"

t_value	*read_json_file(char *filename)
{
	t_value		*map_json;

	if (!(map_json = read_json(filename, 20 * 1024 * 1024)))
	{
		ft_putstr("Failed to read file \"");
		ft_putstr(filename);
		ft_putstr("\"\n");
		return (NULL);
	}
	if (map_json->type == 0)
	{
		ft_putstr("Invalid JSON file\n");
		free_value(map_json);
		return (NULL);
	}
	return (map_json);
}

void	launch_wolf3d(t_wolf3d *wolf3d, t_value *map_json, t_config *config)
{
	if (!init_wolf3d(wolf3d, map_json))
	{
		free_value(map_json);
		return ;
	}
	free_value(map_json);
	if (!init_wolf3d_win(wolf3d, config, "wolf3d - dbousque"))
		return ;
	mlx_loop_hook(wolf3d->window.mlx, loop, (void*)wolf3d);
	mlx_loop(wolf3d->window.mlx);
}

int		show_help(char *command)
{
	ft_putstr("___ wolf3d - dbousque ___\n");
	ft_putstr("Usage : ");
	ft_putstr(command);
	ft_putstr(" <map_file> [config_file]\n\n");
	ft_putstr("  WASD      : move\n");
	ft_putstr("  A/S       : look around\n");
	ft_putstr("  D         : debug mode\n");
	ft_putstr("  H/J       : change time of day\n");
	ft_putstr("  ESC       : exit\n");
	return (0);
}

int		main(int argc, char **argv)
{
	t_wolf3d	wolf3d;
	t_value		*map_json;
	t_config	config;

	if (argc <= 1)
		return (show_help(argv[0]));
	if (!(map_json = read_json_file(argv[1])))
		return (1);
	config.width = 1200;
	config.height = 800;
	config.antialiasing = 0;
	if (argc > 2 && !read_config_file(argv[2], &config))
		return (1);
	launch_wolf3d(&wolf3d, map_json, &config);
	return (0);
}
