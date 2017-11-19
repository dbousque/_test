

#include "irc_client.h"

char	connect_to_server_ipv4(t_env *e, t_opts *opts)
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

char	connect_to_server_ipv6(t_env *e, t_opts *opts)
{
	struct sockaddr_in6	serv_addr;
	struct protoent		*proto;

	proto = getprotobyname("tcp");
	if (!proto)
		return (0);
	e->server_fd = socket(AF_INET6, SOCK_STREAM, proto->p_proto);
	if (e->server_fd == -1)
		return (0);
	serv_addr.sin6_family = AF_INET6;
	serv_addr.sin6_port = htons(opts->port);
	if (inet_pton(AF_INET6, opts->host, &serv_addr.sin6_addr) != 1)
		return (0);
	if (connect(e->server_fd, (struct sockaddr *)&serv_addr,
		sizeof(serv_addr)) == -1)
	{
		return (0);
	}
	e->connected = 1;
	return (1);
}

char	connect_to_server(t_env *e, t_opts *opts)
{
	char	is_ipv6;
	int		i;

	is_ipv6 = 0;
	i = 0;
	while (opts->host[i])
	{
		if (opts->host[i] == ':')
		{
			is_ipv6 = 1;
			break ;
		}
		i++;
	}
	if (is_ipv6)
		return (connect_to_server_ipv6(e, opts));
	return (connect_to_server_ipv4(e, opts));
}

char	try_connect(t_env *e, char *host, char *port)
{
	int		argc;
	char	*argv[3];
	t_opts	opts;

	argc = 2;
	argv[1] = host;
	if (port)
	{
		argc = 3;
		argv[2] = port;
	}
	if (!parse_options(&opts, argc, argv))
		return (1);
	if (e->connected)
	{
		win_write("Disconnecting from current server...\n");
		close(e->server_fd);
		e->connected = 0;
	}
	if (opts.host && opts.port && !connect_to_server(e, &opts))
		win_write("|x Could not connect to server\n");
	return (1);
}

char	reconnect_if_connect_command(t_env *e, char *buffer, int len)
{
	t_msg					msg;
	t_parse_message_res		parse_res;
	int						nb_params;
	char					*port;

	if (!startswith(buffer, "/connect "))
		return (0);
	init_msg(&msg);
	parse_res = parse_message(buffer, len, &msg);
	if (parse_res != COMMAND_OK)
	{
		win_write("|x Invalid /connect command\n");
		return (1);
	}
	if (msg.command != CONNECT)
		return (1);
	nb_params = 0;
	while (msg.params[nb_params])
		nb_params++;
	if (nb_params > 0 && msg.params[nb_params - 1][0] == '\0')
		nb_params--;
	if (nb_params <= 0 || nb_params > 2)
	{
		win_write("|x Wrong number of params for /connect, expects 1 or 2\n");
		return (1);
	}
	port = nb_params > 1 ? msg.params[1] : NULL;
	try_connect(e, msg.params[0], port);
	return (1);
}

void	ft_strcpy(char *dest, char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
}

void	prepend_privmsg(char *buffer, int len)
{
	int		i;

	i = len;
	while (i >= 0)
	{
		buffer[i + 16] = buffer[i];
		i--;
	}
	ft_strcpy(buffer, "/msg ");
	ft_strcpy(buffer + 5, g_priv_user);
	ft_strcpy(buffer + 14, " :");
}

char	read_user_input(t_env *e, char *read_buffer, int *n_chars)
{
	int		ret;
	char	connect_ret;
	char	character;
	char	tmp[2];

	if (*n_chars > READ_BUFFER_SIZE - 3)
	{
		win_write("|x Input too long, flushing it\n");
		read_buffer[0] = '\0';
		*n_chars = 0;
		return (1);
	}
	ret = read(0, &character, 1);
	if (ret == -1 || ret == 0 || character == 4)
	{
		if (ret != -1 && character == 4 && *n_chars)
			return (1);
		close_windows();
		printf(ret == -1 ? "Error while reading input\n" : "Bye\n");
		close(e->server_fd);
		return (0);
	}
	if (character == 127)
	{
		if (*n_chars > 0)
			(*n_chars)--;
		read_buffer[*n_chars] = '\0';
		tmp[0] = ' ';
		tmp[1] = '\0';
		wmove(g_windows.input_win, 0, *n_chars);
		win_input_write(tmp);
		wmove(g_windows.input_win, 0, *n_chars);
		wrefresh(g_windows.input_win);
		return (1);
	}
	read_buffer[*n_chars] = character;
	(*n_chars)++;
	if (character == '\r')
	{
		read_buffer[*n_chars] = '\n';
		(*n_chars)++;
	}
	read_buffer[*n_chars] = '\0';
	if (character != '\r')
	{
		tmp[0] = character;
		tmp[1] = '\0';
		win_input_write(tmp);
		return (1);
	}
	wclear(g_windows.input_win);
	wmove(g_windows.input_win, 0, 0);
	wrefresh(g_windows.input_win);
	if (g_priv_user_mode && !startswith(read_buffer, "/stdmode")
		&& *n_chars + 16 < READ_BUFFER_SIZE - 2)
	{
		prepend_privmsg(read_buffer, *n_chars);
		*n_chars += 16;
	}
	connect_ret = reconnect_if_connect_command(e, read_buffer, *n_chars);
	if (connect_ret == 1)
	{
		*n_chars = 0;
		read_buffer[0] = '\0';
		return (1);
	}
	if (!e->connected)
	{
		*n_chars = 0;
		read_buffer[0] = '\0';
		win_write("You are not connected, connect before sending commands\n");
		return (1);
	}
	if (!connect_ret && (write(e->server_fd, read_buffer, *n_chars)) == -1)
	{
		*n_chars = 0;
		read_buffer[0] = '\0';
		close_windows();
		printf("Error while sending input to server\n");
		close(e->server_fd);
		return (0);
	}
	*n_chars = 0;
	read_buffer[0] = '\0';
	return (1);
}

char	read_server_input(t_env *e, char *buffer)
{
	int		ret;

	ret = read(e->server_fd, buffer, READ_BUFFER_SIZE - 1);
	if (ret == 0)
	{
		win_write("|x Server disconnected\n");
		e->connected = 0;
		e->server_fd = -1;
	}
	if (ret == -1)
	{
		close_windows();
		printf("Error while reading server input\n");
		close(e->server_fd);
		return (0);
	}
	buffer[ret] = '\0';
	if (ret < 4)
		win_write(buffer);
	else
		win_write(buffer);
	return (1);
}

void	update_connected_info(char connected)
{
	wmove(g_windows.info_win, 3, COLS - 37);
	wprintw(g_windows.info_win, "connection ");
	if (connected)
	{
		waddch(g_windows.info_win, ' ' | A_REVERSE | COLOR_PAIR(2));
		waddch(g_windows.info_win, ' ' | A_REVERSE | COLOR_PAIR(2));
	}
	else
	{
		waddch(g_windows.info_win, ' ' | A_REVERSE | COLOR_PAIR(1));
		waddch(g_windows.info_win, ' ' | A_REVERSE | COLOR_PAIR(1));
	}
}

void	update_nick_info(char *nick)
{
	wmove(g_windows.info_win, 3, 2);
	wprintw(g_windows.info_win, "nick : ");
	wwrite(g_windows.info_win, nick);
}

void	set_info(char *nick, char connected)
{
	update_nick_info("          ");
	update_nick_info(nick);
	update_connected_info(connected);
	wrefresh(g_windows.info_win);
	wrefresh(g_windows.input_win);
}

void	update_info(t_env *e)
{
	struct timeval	now;

	if (!e->connected)
	{
		wclear(g_windows.users_win);
		wrefresh(g_windows.users_win);
		set_info("-", 0);
		return ;
	}
	update_connected_info(1);
	wrefresh(g_windows.info_win);
	wrefresh(g_windows.input_win);
	gettimeofday(&now, NULL);
	if (now.tv_sec - e->last_users_update.tv_sec > 4)
	{
		write(e->server_fd, "/users\r\n", 8);
		e->last_users_update = now;
	}
	else if (now.tv_sec - e->last_nick_update.tv_sec > 4)
	{
		write(e->server_fd, "/mynick\r\n", 9);
		e->last_nick_update = now;
	}
	else if (now.tv_sec - e->last_privuser_update.tv_sec > 4)
	{
		write(e->server_fd, "/privuser\r\n", 11);
		e->last_privuser_update = now;
	}
}

void	main_loop(t_env *e, struct timeval *timeout)
{
	char	buffer[READ_BUFFER_SIZE];
	char	read_buffer[READ_BUFFER_SIZE];
	int		n_chars;
	int		highest_fd;
	int		nb_ready;

	n_chars = 0;
	while (1)
	{
		update_info(e);
		FD_ZERO(&(e->read_fds));
		FD_SET(0, &(e->read_fds));
		if (e->connected)
			FD_SET(e->server_fd, &(e->read_fds));
		highest_fd = e->server_fd > 0 ? e->server_fd : 0;
		timeout->tv_sec = 2;
		timeout->tv_usec = 0;
		nb_ready = select(highest_fd + 1, &(e->read_fds), NULL, NULL, timeout);
		if (nb_ready == -1)
			continue ;
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
				if (!read_user_input(e, read_buffer, &n_chars))
					return ;
				nb_ready--;
			}
		}
	}
}

int		main(int argc, char **argv)
{
	t_opts			opts;
	t_env			e;
	struct timeval	timeout;

	g_priv_user_mode = 0;
	init_commands_names();
	init_env(&e);
	if (!parse_options(&opts, argc, argv))
		return (0);
	init_windows();
	if (opts.host && opts.port && !connect_to_server(&e, &opts))
		win_write("|x Could not connect to server\n");
	main_loop(&e, &timeout);
	close_windows();
	return (1);
}