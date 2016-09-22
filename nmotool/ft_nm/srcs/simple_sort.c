/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 17:58:32 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 17:58:34 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	simple_sort(void **elts, int start, int end,
									int (*cmp)(void *elt1, void *elt2))
{
	int		i;
	int		j;
	void	*tmp;

	i = end;
	while (i > 1)
	{
		j = start;
		while (j < i - 1)
		{
			if (cmp(elts[j], elts[j + 1]) > 0)
			{
				tmp = elts[j];
				elts[j] = elts[j + 1];
				elts[j + 1] = tmp;
			}
			j++;
		}
		i--;
	}
}
