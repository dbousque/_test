/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_client3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 16:29:16 by dbousque          #+#    #+#             */
/*   Updated: 2016/12/08 16:30:35 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

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
	return (CMD_RAW_COMMAND);
}

char	*ft_strdup(char *str)
{
	char	*res;
	int		i;

	if (!(res = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	usage(char *command)
{
	ft_putstr("Usage : ");
	ft_putstr(command);
	ft_putstr(" <host> <port[1-65535]>\n");
	exit(-1);
}
