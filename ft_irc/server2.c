

#include "ft_irc.h"

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;
	int					ret;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (sock == -1)
		return (-1);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(sock, (const struct sockaddr*)&sin, sizeof(sin));
	if (ret == -1)
		return (-1);
	ret = listen(sock, MAX_NB_CONNECTIONS);
	if (ret == -1)
		return (-1);
	return (sock);
}

void	read_user_input(t_user *users, int i, t_list *channels, int nb_users)
{
	t_user	*user;
	int		ret;

	user = &(users[i]);
	ret = read(user->fd, user->read_buffer, 512);
	if (ret <= 0)
	{
		if (ret == 0)
			LOG(INFO, "user '%s' exiting\n", user->nickname);
		else
			LOG(ERROR, "error while reading '%s' input\n", user->nickname);
		remove_user(users, i, nb_users);
		return ;
	}
	user->read_buffer[ret] = '\0';
	LOG(INFO, "user sent : %s\n", user->read_buffer);
}

void	write_user_output(t_user *users, int i, t_list *channels, int nb_users)
{

}

void	perform_select(t_env *e, int highest_fd)
{
	int		nb_ready;
	int		i;

	nb_ready = select(highest_fd + 1, &(e->read_fds), &(e->write_fds), NULL, NULL);
	if (nb_ready == -1)
	{
		LOG(ERROR, "select error");
		return ;
	}
	if (nb_ready > 0)
	{
		LOG(INFO, "%d fd%s ready", nb_ready, nb_ready == 1 ? "" : "s");
		if (FD_ISSET(e->sock_fd, &(e->read_fds)))
		{
			accept_user(e->sock_fd, e->users, &(e->nb_users));
			nb_ready--;
		}
		i = 0;
		while (i < e->nb_users && nb_ready > 0)
		{
			if (FD_ISSET((e->users)[i].fd, &(e->read_fds)))
			{
				read_user_input(e->users, i, &(e->channels), e->nb_users);
				nb_ready--;
			}
			if (FD_ISSET((e->users)[i].fd, &(e->write_fds)))
			{
				write_user_output(e->users, i, &(e->channels), e->nb_users);
				nb_ready--;
			}
			i++;
		}
		if (nb_ready > 0)
			LOG(DEBUG, "weird thing, nb_ready at %d, but no client left", nb_ready);
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
		LOG(INFO, "loop start, nb_users %d", e->nb_users);
		FD_ZERO(&(e->write_fds));
		FD_ZERO(&(e->read_fds));
		FD_SET(e->sock_fd, &(e->read_fds));
		highest_fd = e->sock_fd;
		i = 0;
		while (i < e->nb_users)
		{
			if (e->users[i].fd > highest_fd)
				highest_fd = e->users[i].fd;
			FD_SET(e->users[i].fd, &(e->read_fds));
			if (e->users[i].nb_in_write_buffer > 0)
				FD_SET(e->users[i].fd, &(e->write_fds));
			i++;
		}
		perform_select(e, highest_fd);
	}
}

int		main(void)
{
	int		port;
	t_env	e;

	srand(time(NULL));
	init_commands_names();
	port = 4242;
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
}