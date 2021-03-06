/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:08:13 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 17:09:08 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	too_big_len_ten(char *str, char signe, int len)
{
	int		i;
	char	*int_max;

	int_max = "2147483647";
	i = 0;
	while (i < len)
	{
		if (i == 9)
		{
			if (str[i] > '8' || (signe == 0 && str[i] > '7'))
				return (1);
		}
		else if (str[i] > int_max[i])
			return (1);
		i++;
	}
	return (0);
}

char	too_big_for_int(char *str)
{
	int		len;
	char	signe;

	signe = 0;
	if (str[0] == '-')
	{
		signe = 1;
		str++;
	}
	len = ft_strlen(str);
	if (len > 10)
		return (1);
	else if (len == 10)
		return (too_big_len_ten(str, signe, len));
	return (0);
}

char	no_nb(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (0);
		i++;
	}
	return (1);
}

int		*get_nbs(int argc, char **argv)
{
	int		*nbs;
	int		i;

	if (!(nbs = (int*)malloc(sizeof(int) * (argc - 1))))
		return (NULL);
	i = 1;
	while (i < argc)
	{
		if (invalid_char(argv[i]) || too_big_for_int(argv[i]) || no_nb(argv[i]))
		{
			free(nbs);
			return (NULL);
		}
		nbs[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	return (nbs);
}
