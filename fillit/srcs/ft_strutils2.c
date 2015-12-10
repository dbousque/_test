/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strutils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:20:53 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/08 11:43:19 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_strstrlen(char **strstr)
{
	int		i;

	i = 0;
	while (strstr[i])
		i++;
	return (i);
}

char	**ft_strstrdup(char **strstr)
{
	int		i;
	int		x;
	char	**res;

	i = ft_strstrlen(strstr);
	if (!(res = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	res[i] = NULL;
	i = 0;
	while (strstr[i])
	{
		x = ft_strlen(strstr[i]);
		if (!(res[i] = (char*)malloc(sizeof(char) * (x + 1))))
			return (NULL);
		res[i][x] = '\0';
		x = 0;
		while (strstr[i][x])
		{
			res[i][x] = strstr[i][x];
			x++;
		}
		i++;
	}
	return (res);
}

void	ft_void_int(int res[26])
{
	int		i;

	i = 0;
	while (i < 26)
	{
		res[i] = 0;
		i++;
	}
}

int		ft_char_in_line(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '.')
			return (1);
		i++;
	}
	return (0);
}
