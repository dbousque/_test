

#include "ft_irc.h"

void	welcome_user_to_channel(t_user *user, t_channel *channel)
{
	char	msg[600];

	snprintf(msg, 600, "Welcome to '%s'\nDescription : %s",
										channel->name, channel->description);
	log_user(user, msg);
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

char	befriends(t_user *user1, t_user *user2)
{
	int		i;

	i = 0;
	while (user1->friends[i] != -1)
	{
		if (user1->friends[i] == user2->id)
			return (1);
		i++;
	}
	return (0);
}

int		print_usage(char **argv)
{
	printf("Usage : %s <port:uint16_t>\n", argv[0]);
	return (0);
}

t_user	*find_user_by_nick(t_env *e, char *nick)
{
	t_user	*tmp_user;
	int		i;

	i = 0;
	while (i < e->nb_users)
	{
		tmp_user = &(e->users[i]);
		if (!tmp_user->free && ft_streq(tmp_user->nickname, nick))
			return (tmp_user);
		i++;
	}
	return (NULL);
}
