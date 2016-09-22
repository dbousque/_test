/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ran_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 17:53:15 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 17:53:18 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char	*get_current_ar_name(char *ptr)
{
	static char		*str = NULL;

	if (ptr)
		str = ptr;
	return (str);
}

size_t	end_of_name(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	if ((((long)str + i)) % 8 == 0)
		return (i + 8);
	if ((((long)str + i)) % 8 <= 4)
		return (i - ((((long)str + i)) % 8) + 8);
	return (i - ((((long)str + i)) % 8) + 16);
}

int		cmp_rans(void *elt1, void *elt2)
{
	struct ranlib	*ran1;
	struct ranlib	*ran2;

	ran1 = elt1;
	ran2 = elt2;
	if (ran1->ran_off < ran2->ran_off)
		return (-1);
	if (ran1->ran_off == ran2->ran_off)
		return (0);
	return (1);
}
