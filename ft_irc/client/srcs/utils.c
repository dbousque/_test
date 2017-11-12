

#include "irc_client.h"

void	init_env(t_env *e)
{
	e->connected = 0;
	e->server_fd = -1;
}

int		parse_port(char *str)
{
	int		res;
	int		i;

	i = 0;
	res = 0;
	if (str[0] == '0')
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + (str[i] - '0');
		if (res > 65535)
			return (-1);
		i++;
	}
	return (res);
}

char	ft_streq(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (!str1[i] && !str2[i])
		return (1);
	return (0);
}

char	parse_options(t_opts *opts, int argc, char **argv)
{
	opts->host = NULL;
	opts->port = SERVER_DEFAULT_PORT;
	if (argc > 1)
	{
		if (ft_streq(argv[1], "localhost"))
			opts->host = "127.0.0.1";
		else
			opts->host = argv[1];
	}
	if (argc > 2)
	{
		opts->port = parse_port(argv[2]);
		if (opts->port == -1)
		{
			printf("Invalid port\n");
			return (0);
		}
	}
	return (1);
}
