

#include "ft_irc.h"

int	 create_server(int port)
{
	int				 sock;
	struct protoent	 *proto;
	struct sockaddr_in	sin;
	int				 ret;

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

int	 unique_user_id(t_user *users, int nb_users)
{
	int	i;
	int	id;

	id = -1;
	while (1)
	{
		id = rand();
		if (id < 1)
		i = 0;
		while (i < nb_users)
		{
			if (users[i].id == id)
			{
				id = -1;
				break ;
			}
			i++;
		}
		if (id != -1)
			break ;
	}
	return (id);
}

char	ft_streq(char *str1, char *str2)
{
	int	 i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (!str1[i] && !str2[i])
		return (1);
	return (0);
}

void	set_unique_nickname(t_user *user, t_user *users, int nb_users)
{
	int	i;
	char	ok;

	while (1)
	{
		i = 0;
		while (i < 9)
		{
			user->nickname[i] = (rand() % 26) + 'a';
			i++;
		}
		user->nickname[9] = '\0';
		ok = 1;
		i = 0;
		while (i < nb_users)
		{
			if (ft_streq(user->nickname, users[i].nickname))
			{
				ok = 0;
				break ;
			}
			i++;
		}
		if (ok)
			return ;
	}
}

void	accept_user(int sock_fd, t_user *users, int *nb_users)
{
	struct sockaddr_in	sin;
	socklen_t len;
	t_user		*user;
	char			*ip_name;
	int		 i;

	user = &(users[*nb_users]);
	user->fd = accept(sock_fd, (struct sockaddr*)&sin, &len);
	if (user->fd == -1)
	{
		printf("accept failed");
		return ;
	}
	user->free = 0;
	user->id = unique_user_id(users, *nb_users);
	user->nb_in_write_buffer = 0;
	user->nb_in_read_buffer = 0;
	user->channels[0] = -1;
	user->nickname[0] = '\0';
	set_unique_nickname(user, users, *nb_users);
	user->msg_sent = 0;
	user->command_sent = 0;
	user->mode = STD;
	user->priv_msg_user = 0;
	user->friends[0] = -1;
	ip_name = inet_ntoa(sin.sin_addr);
	i = 0;
	while (ip_name[i] && i < 19)
	{
		user->ip_name[i] = ip_name[i];
		i++;
	}
	user->ip_name[i] = '\0';
	printf("client IP : %s\n", user->ip_name);
	(*nb_users)++;
}

void	remove_user_from_friends(int *friends, int id)
{
	int		i;
	int		decal;

	decal = 0;
	i = 0;
	while (friends[i + decal] != -1)
	{
		while (friends[i + decal] == id)
			decal++;
		if (decal > 0)
			friends[i] = friends[i + decal];
		i++;
	}
	friends[i] = -1;
}

void	remove_user(t_user *users, int i, int nb_users)
{
	t_user	*user;

	user = &(users[i]);
	close(user->fd);
	i = 0;
	while (i < nb_users)
	{
		if (!users[i].free)
		{
			if (users[i].mode == PRIV_MSG && users[i].priv_msg_user == user->id)
			{
				users[i].mode = STD;
				users[i].priv_msg_user = -1;
			}
			remove_user_from_friends(users[i].friends, user->id);
		}
		i++;
	}
	user->free = 1;
	user->id = -1;
	user->nickname[0] = '\0';
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

void	init_commands_names(void)
{
	g_irc_commands[0] = "/nick";
	g_irc_commands[1] = "/join";
	g_irc_commands[2] = "/leave";
	g_irc_commands[3] = "/who";
	g_irc_commands[4] = "/msg";
	g_irc_commands[5] = "/connect";
	g_irc_commands[6] = NULL;
}

void	init_users(t_user *users)
{
	int		i;

	i = 0;
	while (i < MAX_NB_CONNECTIONS)
	{
		users[i].free = 1;
		i++;
	}
}

void	clear_removed_users(t_user *users, int *nb_users)
{
	int		i;
	int		decal;

	decal = 0;
	i = 0;
	while (i + decal < *nb_users)
	{
		while (users[i + decal].free && i + decal < *nb_users)
			decal++;
		if (decal > 0 && i + decal < *nb_users)
			users[i] = users[i + decal];
		i++;
	}
	*nb_users -= decal;
}

int	 main(void)
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