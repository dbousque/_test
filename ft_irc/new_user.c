

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

void	set_unique_nickname(t_user *user, t_user *users, int nb_users)
{
	int		i;
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

void	init_user(t_user *users, t_user *user, int nb_users,
													struct sockaddr_in *sin)
{
	char	*ip_name;
	int		i;

	user->free = 0;
	user->id = unique_user_id(users, nb_users);
	user->nb_in_write_buffer = 0;
	user->nb_in_read_buffer = 0;
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

	user = &(users[*nb_users]);
	user->fd = accept(sock_fd, (struct sockaddr*)&sin, &len);
	if (user->fd == -1)
	{
		LOG(DEBUG, "accept failed");
		return ;
	}
	init_user(users, user, *nb_users, &sin);
	LOG(INFO, "new client : '%s' from %s", user->nickname, user->ip_name);
	(*nb_users)++;
}