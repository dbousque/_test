/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 18:17:14 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/12 18:24:53 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	rebuild_to_sort(void **to_sort, void **part1, void **part2, void *pivot)
{
	int		i;
	int		decal;

	i = 0;
	while (part1[i])
	{
		to_sort[i] = part1[i];
		i++;
	}
	to_sort[i] = pivot;
	decal = i + 1;
	i = 0;
	while (part2[i])
	{
		to_sort[decal + i] = part2[i];
		i++;
	}
}

char	is_s(void **to_sort, int nb,
			int (*compare_fct)(void *elt1, void *elt2, void *elt3), void *elt3)
{
	if (nb <= 1)
		return (1);
	nb--;
	while (nb > 0)
	{
		if (compare_fct(to_sort[nb], to_sort[nb - 1], elt3) > 0)
			return (0);
		nb--;
	}
	return (1);
}

char	in(int nb1_2[2], void **pivot, int *nb, void **to_sort)
{
	*pivot = to_sort[*nb - 1];
	*nb -= 1;
	nb1_2[0] = 0;
	nb1_2[1] = 0;
	return (0);
}

void	quicksort(void **to_sort, int nb,
			int (*compare_fct)(void *elt1, void *elt2, void *elt3), void *elt3)
{
	void	*part1_2[2][nb];
	void	*pivot;
	int		nb1_2[2];

	pivot = NULL;
	if (is_s(to_sort, nb, compare_fct, elt3) || in(nb1_2, &pivot, &nb, to_sort))
		return ;
	while (--nb >= 0)
	{
		if (compare_fct(pivot, to_sort[nb], elt3) < 0)
		{
			part1_2[0][nb1_2[0]] = to_sort[nb];
			(nb1_2[0])++;
		}
		else
		{
			part1_2[1][nb1_2[1]] = to_sort[nb];
			(nb1_2[1])++;
		}
	}
	part1_2[0][nb1_2[0]] = NULL;
	part1_2[1][nb1_2[1]] = NULL;
	quicksort(part1_2[0], nb1_2[0], compare_fct, elt3);
	quicksort(part1_2[1], nb1_2[1], compare_fct, elt3);
	rebuild_to_sort(to_sort, part1_2[0], part1_2[1], pivot);
}

void	insertion_sort(void **to_sort, int nb,
			int (*compare_fct)(void *elt1, void *elt2, void *elt3), void *elt3)
{
	int		i;
	int		j;
	void	*tmp;

	i = 1;
	if (nb == 1)
		return ;
	while (i < nb)
	{
		j = i;
		while (j > 0 && compare_fct(to_sort[j], to_sort[j - 1], elt3) > 0)
		{
			tmp = to_sort[j];
			to_sort[j] = to_sort[j - 1];
			to_sort[j - 1] = tmp;
			j--;
		}
		i++;
	}
}
