

#include "ft_irc.h"

int		unique_user_id(t_user *users, int nb_users)
{
	int		i;
	int		id;

	id = -1;
	while (1)
	{
		id = rand();
		if (id < 1)
			continue ;
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

void	set_unique_nickname(t_user *user, t_user *users, int nb_users)
{
	int		i;
	char	ok;

	while (1)
	{
		i = 0;
		while (i < 5)
		{
			user->nickname[i] = (rand() % 26) + 'a';
			i++;
		}
		user->nickname[5] = '\0';
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

void	init_user(t_user *users, t_user *user, int nb_users,
													struct sockaddr_in *sin)
{
	char	*ip_name;
	int		i;

	user->free = 0;
	user->id = unique_user_id(users, nb_users);
	init_circular_buffer(&(user->read_buffer));
	init_circular_buffer(&(user->write_buffer));
	user->channels[0] = -1;
	user->nickname[0] = '\0';
	set_unique_nickname(user, users, nb_users);
	user->msg_sent = 0;
	user->command_sent = 0;
	user->mode = STD;
	user->priv_msg_user = 0;
	user->friends[0] = -1;
	ip_name = inet_ntoa(sin->sin_addr);
	i = 0;
	while (ip_name[i] && i < 19)
	{
		user->ip_name[i] = ip_name[i];
		i++;
	}
	user->ip_name[i] = '\0';
}

void	accept_user(int sock_fd, t_user *users, int *nb_users)
{
	struct sockaddr_in	sin;
	socklen_t			len;
	t_user				*user;

	if (*nb_users >= MAX_NB_CONNECTIONS)
	{
		LOG(INFO, "Could not accept new client, too many clients");
		return ;
	}
	user = &(users[*nb_users]);
	user->fd = accept(sock_fd, (struct sockaddr*)&sin, &len);
	if (user->fd == -1)
	{
		LOG(DEBUG, "accept failed");
		return ;
	}
	init_user(users, user, *nb_users, &sin);
	LOG(INFO, "New client : '%s' from %s", user->nickname, user->ip_name);
	log_user(user, "|> Welcome to this amazing IRC server");
	snprintf(g_tmp_buffer, USER_BUFFER_SIZE,
									"Your nickname is '%s'", user->nickname);
	log_user(user, g_tmp_buffer);
	(*nb_users)++;
}