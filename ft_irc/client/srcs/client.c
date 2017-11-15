

#include "irc_client.h"

char	connect_to_server(t_env *e, t_opts *opts)
{
	struct sockaddr_in	serv_addr;
	struct protoent		*proto;

	proto = getprotobyname("tcp");
	if (!proto)
		return (0);
	e->server_fd = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (e->server_fd == -1)
		return (0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(opts->port);
	serv_addr.sin_addr.s_addr = inet_addr(opts->host);
	if ((int)serv_addr.sin_addr.s_addr == -1)
		return (0);
	if (connect(e->server_fd, (struct sockaddr *)&serv_addr,
		sizeof(serv_addr)) == -1)
	{
		return (0);
	}
	e->connected = 1;
	return (1);
}

char	try_connect(t_env *e, char *host, char *port)
{
	int		argc;
	char	*argv[2];
	t_opts	opts;

	argc = 1;
	argv[0] = host;
	if (port)
	{
		argc = 2;
		argv[1] = port;
	}
	if (!parse_options(&opts, argc, argv))
		return (0);
	if (opts.host && opts.port && !connect_to_server(e, &opts))
		printf("Could not connect to server\n");
	return (0);
}

char	reconnect_if_connect_command(t_env *e, char *buffer)
{
	int		i;
	char	*host;
	char	tmp;
	char	tmp2;
	int		end;

	if (!startswith(buffer, "/connect "))
		return (0);
	buffer += 9;
	while (*buffer == ' ')
		buffer++;
	host = buffer;
	i = 0;
	while (buffer[i] && buffer[i] != ' ' && buffer[i] != '\r')
		i++;
	end = i;
	while (buffer[i] == ' ')
		i++;
	if ((!buffer[i] || buffer[i] == '\r') && end == 0)
		return (0);
	if (!buffer[i] || buffer[i] == '\r')
	{
		tmp = buffer[end];
		buffer[end] = '\0';
		tmp2 = try_connect(e, host, NULL);
		buffer[end] = tmp;
		return (tmp2);
	}
	buffer += i;
	i = 0;
	while (buffer[i] >= '0' && buffer[i] <= '9')
		i++;
	if (i == 0)
		return (0);
	buffer[i] = '\0';
	return (try_connect(e, host, buffer));
}

char	send_user_input_to_server(t_env *e, char *buffer)
{
	int		ret;
	char	connect_ret;

	ret = read(0, buffer, READ_BUFFER_SIZE - 2);
	if (ret == -1 || ret == 0)
	{
		printf(ret == -1 ? "Error while reading input\n" : "Bye\n");
		close(e->server_fd);
		return (0);
	}
	if (buffer[ret - 1] == '\n')
	{
		buffer[ret - 1] = '\r';
		buffer[ret] = '\n';
		ret++;
	}
	buffer[ret] = '\0';
	connect_ret = reconnect_if_connect_command(e, buffer);
	if (connect_ret == -1)
		return (0);
	if (connect_ret == 1)
		return (1);
	if (e->server_fd == -1)
	{
		printf("You are not connected, connect before sending commands\n");
		return (1);
	}
	if (!connect_ret && (write(e->server_fd, buffer, ret)) == -1)
	{
		printf("Error while sending input to server\n");
		close(e->server_fd);
		return (0);
	}
	return (1);
}

char	green_instruction(char *str, int ind)
{
	if (str[ind] == '|' && str[ind + 1] == '>' && str[ind + 2] == ' ')
		return (1);
	return (0);
}

char	red_instruction(char *str, int ind)
{
	if (str[ind] == '|' && str[ind + 1] == 'x' && str[ind + 2] == ' ')
		return (1);
	return (0);
}

void	maybe_green_or_red_instruction(char *buffer, int *start)
{
	if (green_instruction(buffer, *start))
	{
		write(1, "\033[1;32m", 7);
		*start += 3;
	}
	else if (red_instruction(buffer, *start))
	{
		write(1, "\033[1;31m", 7);
		*start += 3;
	}
}

void	write_server_output(char *buffer, int ret)
{
	int		start;
	int		i;

	start = 0;
	maybe_green_or_red_instruction(buffer, &start);
	i = start;
	while (i < ret)
	{
		if (buffer[i] == '\n')
		{
			write(1, buffer + start, i - start + 1);
			write(1, "\033[0m", 4);
			start = i + 1;
			maybe_green_or_red_instruction(buffer, &start);
		}
		i++;
	}
	if (i - start > 1)
		write(1, buffer + start, i - start);
	write(1, "\033[0m", 4);
}

char	read_server_input(t_env *e, char *buffer)
{
	int		ret;

	ret = read(e->server_fd, buffer, READ_BUFFER_SIZE - 1);
	if (ret == -1)
	{
		printf("Error while reading server input\n");
		close(e->server_fd);
		return (0);
	}
	buffer[ret] = '\0';
	if (ret < 4)
		write(1, buffer, ret);
	else
		write_server_output(buffer, ret);
	return (1);
}

void	main_loop(t_env *e)
{
	char	buffer[READ_BUFFER_SIZE];
	int		highest_fd;
	int		nb_ready;

	while (1)
	{
		FD_ZERO(&(e->read_fds));
		FD_SET(0, &(e->read_fds));
		if (e->connected)
			FD_SET(e->server_fd, &(e->read_fds));
		highest_fd = e->server_fd > 0 ? e->server_fd : 0;
		nb_ready = select(highest_fd + 1, &(e->read_fds), NULL, NULL, NULL);
		if (nb_ready == -1)
		{
			printf("Select error\n");
			close(e->server_fd);
			return ;
		}
		if (nb_ready > 0)
		{
			if (e->connected && FD_ISSET(e->server_fd, &(e->read_fds)))
			{
				if (!read_server_input(e, buffer))
					return ;
				nb_ready--;
			}
			if (nb_ready > 0 && FD_ISSET(0, &(e->read_fds)))
			{
				if (!send_user_input_to_server(e, buffer))
					return ;
				nb_ready--;
			}
		}
	}
}

int		main(int argc, char **argv)
{
	t_opts	opts;
	t_env	e;

	init_env(&e);
	if (!parse_options(&opts, argc, argv))
		return (0);
	if (opts.host && opts.port && !connect_to_server(&e, &opts))
		printf("Could not connect to server\n");
	main_loop(&e);
	return (1);
}