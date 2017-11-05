

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
			printf("user '%s' exiting\n", user->nickname);
		else
			printf("error while reading '%s' input\n", user->nickname);
		remove_user(users, i, nb_users);
		return ;
	}
	user->read_buffer[ret] = '\0';
	printf("user sent : %s\n", user->read_buffer);
}

void	write_user_output(t_user *users, int i, t_list *channels, int nb_users)
{

}

int		main(void)
{
	int		port;
	int		sock_fd;
	fd_set	read_fds;
	fd_set	write_fds;
	t_user	users[MAX_NB_CONNECTIONS];
	int		nb_users;
	t_list	channels;

	port = 4242;
	if ((sock_fd = create_server(port)) == -1)
	{
		printf("could not create server on port %d\n", port);
		return (1);
	}
	srand(time(NULL));
	nb_users = 0;
	init_commands_names();
	init_users(users);
	if (!(init_list(&channels, sizeof(t_channel))))
	{
		printf("could not initialize\n");
		return (1);
	}
	while (1)
	{
		printf("loop start, nb_users %d\n", nb_users);

		FD_ZERO(&write_fds);
		FD_ZERO(&read_fds);

		FD_SET(sock_fd, &read_fds);

		int highest_fd = sock_fd;

		int i = 0;
		while (i < nb_users)
		{
			if (users[i].fd > highest_fd)
				highest_fd = users[i].fd;
			FD_SET(users[i].fd, &read_fds);
			if (users[i].nb_in_write_buffer > 0)
				FD_SET(users[i].fd, &write_fds);
			i++;
		}

		int nb_ready = select(highest_fd + 1, &read_fds, &write_fds, NULL, NULL);
		if (nb_ready == -1)
		{
			printf("select error\n");
			continue ;
		}
		if (nb_ready > 0)
		{
			printf("%d fds ready\n", nb_ready);
			if (FD_ISSET(sock_fd, &read_fds))
			{
				accept_user(sock_fd, users, &nb_users);
				nb_ready--;
			}
			i = 0;
			while (i < nb_users && nb_ready > 0)
			{
				if (FD_ISSET(users[i].fd, &read_fds))
				{
					read_user_input(users, i, &channels, nb_users);
					nb_ready--;
				}
				if (FD_ISSET(users[i].fd, &write_fds))
				{
					write_user_output(users, i, &channels, nb_users);
					nb_ready--;
				}
				i++;
			}
			if (nb_ready > 0)
				printf("weird thing, nb_ready at %d, but no client left\n", nb_ready);
			clear_removed_users(users, &nb_users);
		}
	}
	return (0);
}