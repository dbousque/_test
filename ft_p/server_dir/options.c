

#include "ft_p_server.h"

int		parse_port(char *port)
{
	size_t	i;
	int		res;

	i = 0;
	while (port[i] && port[i] >= '0' && port[i] <= '9')
		i++;
	if (port[i] != '\0' || i > 5)
		return (0);
	i = 0;
	res = 0;
	while (port[i])
	{
		res = res * 10 + (port[i] - '0');
		i++;
	}
	return (res);
}

void	parse_options(int argc, char **argv, t_options *options)
{
	options->strict = 0;
	if (argc > 4)
	{
		options->error = 1;
		return ;
	}
	if (argc > 2)
	{
		if (chdir(argv[2]) == -1)
		{
			ft_putstr("invalid start directory\n");
			options->error = 1;
			return ;
		}
		if (argc == 4 && ft_strcmp(argv[3], "strict") == 0)
			options->strict = 1;
	}
	options->port = parse_port(argv[1]);
	if (options->port < 1 || options->port > 65535)
	{
		options->error = 1;
		return ;
	}
	options->log = 1;
}