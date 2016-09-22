/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 17:37:30 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 17:40:28 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	rep_tmp(void **elts, int start, int end, void **tmp)
{
	int		i;

	i = start;
	while (i < end)
	{
		elts[i] = tmp[i - start];
		i++;
	}
}

void	swap_n_incr(void **elts, void **tmp, int *x, int *other)
{
	tmp[*x] = elts[*other];
	(*x)++;
	(*other)++;
}

void	merge(void **elts, int start, int end,
									int (*cmp)(void *elt1, void *elt2))
{
	void	*tmp[end - start];
	int		i;
	int		j;
	int		x;

	x = 0;
	i = start;
	j = start + ((end - start) / 2);
	while (1)
	{
		if (i == start + ((end - start) / 2) && j == end)
			break ;
		while (i < start + ((end - start) / 2)
				&& (j == end || cmp(elts[i], elts[j]) <= 0))
			swap_n_incr(elts, tmp, &x, &i);
		while (j < end && (i == start + ((end - start) / 2)
					|| cmp(elts[j], elts[i]) < 0))
			swap_n_incr(elts, tmp, &x, &j);
	}
	rep_tmp(elts, start, end, tmp);
}

void	my_mergesort(void **elts, int start, int end,
									int (*cmp)(void *elt1, void *elt2))
{
	if (end - start <= 1)
		return ;
	my_mergesort(elts, start, start + ((end - start) / 2), cmp);
	my_mergesort(elts, start + ((end - start) / 2), end, cmp);
	merge(elts, start, end, cmp);
}
