/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:08:49 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 17:09:00 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	twice_same(int argc, int *nbs)
{
	int		i;
	int		x;

	i = 0;
	while (i < argc)
	{
		x = 0;
		while (x < argc)
		{
			if (i != x && nbs[i] == nbs[x])
				return (1);
			x++;
		}
		i++;
	}
	return (0);
}

char	invalid_char(char *st)
{
	int		i;

	i = 0;
	if (st[0] == '-')
		st++;
	while (st[i])
	{
		if (st[i] < '0' || st[i] > '9' || (st[0] == '0' && ft_strlen(st) > 1))
			return (1);
		i++;
	}
	return (0);
}
