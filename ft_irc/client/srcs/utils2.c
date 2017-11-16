

#include "irc_client.h"

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	contains(char *str, int len, char c)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void		init_commands_names(void)
{
	g_irc_commands[0] = "/connect";
	g_irc_commands[1] = NULL;
}
