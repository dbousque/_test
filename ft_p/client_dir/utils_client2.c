

#include "ft_p_client.h"

char	char_in_str(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_strcpy(char *str1, char *str2, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		str1[i] = str2[i];
		i++;
	}
}

int		ind_of_char(char *str, char c, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\f');
}

char	command_is(char *command, char *is)
{
	int		i;

	i = 0;
	while (command[i] && is[i] && command[i] == is[i])
		i++;
	return ((size_t)i == ft_strlen(is) && is_space(command[i]));
}

char	get_type_of_command(char *command)
{
	if (command_is(command, "put"))
		return (CMD_PUT);
	if (command_is(command, "get"))
		return (CMD_GET);
	if (command_is(command, "cd"))
		return (CMD_CD);
	return (CMD_RAW_COMMAND);
}