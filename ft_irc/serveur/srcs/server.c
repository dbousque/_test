

#include "ft_irc.h"

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in6	sin;
	int					ret;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(AF_INET6, SOCK_STREAM, proto->p_proto);
	if (sock == -1)
		return (-1);
	ret = 0;
	setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, &ret, sizeof(int));
	sin.sin6_family = AF_INET6;
	sin.sin6_port = htons(port);
	sin.sin6_addr = in6addr_any;
	ret = bind(sock, (const struct sockaddr*)&sin, sizeof(sin));
	if (ret == -1)
		return (-1);
	ret = listen(sock, MAX_NB_CONNECTIONS);
	if (ret == -1)
		return (-1);
	return (sock);
}

void	handle_user_fds(t_env *e, int nb_ready)
{
	int		i;

	i = 0;
	while (i < e->nb_users && nb_ready > 0)
	{
		if (FD_ISSET((e->users)[i].fd, &(e->write_fds)))
		{
			write_user_output(e, i);
			nb_ready--;
		}
		if (FD_ISSET((e->users)[i].fd, &(e->read_fds)))
		{
			read_user_input(e, i);
			nb_ready--;
		}
		i++;
	}
	if (nb_ready > 0)
		LOG(DEBUG, "nb_ready at %d, but no client left", nb_ready);
}

void	perform_select(t_env *e, int highest_fd)
{
	int		nb_ready;

	nb_ready = select(highest_fd + 1, &(e->read_fds), &(e->write_fds),
																NULL, NULL);
	if (nb_ready == -1)
	{
		LOG(ERROR, "select error");
		return ;
	}
	if (nb_ready > 0)
	{
		LOG(DEBUG, "%d fd%s ready", nb_ready, nb_ready == 1 ? "" : "s");
		if (FD_ISSET(e->sock_fd, &(e->read_fds)))
		{
			accept_user(e->sock_fd, e->users, &(e->nb_users));
			nb_ready--;
		}
		handle_user_fds(e, nb_ready);
		clear_removed_users(e->users, &(e->nb_users));
	}
}

void	main_loop(t_env *e)
{
	int		highest_fd;
	int		i;

	e->nb_users = 0;
	while (1)
	{
		LOG(DEBUG, "Loop start, nb_users %d", e->nb_users);
		FD_ZERO(&(e->write_fds));
		FD_ZERO(&(e->read_fds));
		FD_SET(e->sock_fd, &(e->read_fds));
		highest_fd = e->sock_fd;
		i = 0;
		while (i < e->nb_users)
		{
			if (e->users[i].fd > highest_fd)
				highest_fd = e->users[i].fd;
			if (!empty(&(e->users[i].write_buffer)))
				FD_SET(e->users[i].fd, &(e->write_fds));
			FD_SET(e->users[i].fd, &(e->read_fds));
			i++;
		}
		perform_select(e, highest_fd);
	}
}

int		main(int argc, char **argv)
{
	int		port;
	t_env	e;

	if (argc != 2)
	{
		printf("Usage : %s <port:uint16_t>\n", argv[0]);
		return (0);
	}
	if ((port = parse_port(argv[1])) == -1)
	{
		printf("Invalid port\n");
		return (0);
	}
	srand(time(NULL));
	init_commands_names();
	if ((e.sock_fd = create_server(port)) == -1)
	{
		LOG(ERROR, "could not create server on port %d", port);
		return (1);
	}
	init_users(e.users);
	if (!(init_list(&(e.channels), sizeof(t_channel))))
	{
		LOG(ERROR, "could not initialize");
		return (1);
	}
	main_loop(&e);
	return (1);
}