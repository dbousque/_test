/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_client2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 16:29:11 by dbousque          #+#    #+#             */
/*   Updated: 2016/12/08 16:29:13 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
