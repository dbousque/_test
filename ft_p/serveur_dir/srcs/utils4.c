/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 15:55:45 by dbousque          #+#    #+#             */
/*   Updated: 2016/12/08 15:55:47 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

void	ft_strcpy2(char *str1, char *str2, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		str1[i] = str2[i];
		i++;
	}
}

void	get_current_dir(char **res)
{
	size_t	size;

	size = 256;
	if (!(*res = (char*)malloc(sizeof(char) * size)))
	{
		*res = NULL;
		return ;
	}
	while (!(getcwd(*res, size)))
	{
		free(*res);
		size *= 2;
		*res = (char*)malloc(sizeof(char) * size);
		if (!*res)
		{
			*res = NULL;
			return ;
		}
	}
}

char	ft_startswith(char *base, char *start)
{
	int		i;

	i = 0;
	while (base[i] && start[i] && base[i] == start[i])
		i++;
	if (start[i] != '\0')
		return (0);
	return (1);
}

char	always_executable(char *command)
{
	if (ft_strcmp(command, "ls") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "rmdir") == 0)
		return (1);
	if (ft_strcmp(command, "unlink") == 0)
		return (1);
	if (ft_strcmp(command, "mkdir") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	return (0);
}
