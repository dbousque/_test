

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