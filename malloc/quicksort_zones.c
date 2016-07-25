/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_zones.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:52:51 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 16:02:42 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	get_nb_smaller(t_sort_zone *array, int start, int end,
							int (*cmp)(t_sort_zone *elt1, t_sort_zone *elt2))
{
	int		nb_smaller;
	int		i;

	nb_smaller = 0;
	i = start;
	while (i < end - 1)
	{
		if (cmp(&(array[i]), &(array[end - 1])) < 0)
			nb_smaller++;
		i++;
	}
	return (nb_smaller);
}

static void	swap_arr(t_sort_zone *array, int a, int z)
{
	t_sort_zone	tmp;

	tmp = array[a];
	array[a] = array[z];
	array[z] = tmp;
}

void		init_vars(int *a, int *z, int start, int end)
{
	*a = start;
	*z = end - 1;
}

void		quicksort_zones(t_sort_zone *array, int start, int end,
							int (*cmp)(t_sort_zone *elt1, t_sort_zone *elt2))
{
	int		n;
	int		a;
	int		z;

	if (end - start <= 1)
		return ;
	n = get_nb_smaller(array, start, end, cmp);
	swap_arr(array, start + n, end - 1);
	init_vars(&a, &z, start, end);
	while (1)
	{
		while (a < start + n && cmp(&(array[a]), &(array[start + n])) < 0)
			a++;
		if (a >= start + n)
			break ;
		while (z > start + n && cmp(&(array[z]), &(array[start + n])) > 0)
			z--;
		if (z <= start + n)
			break ;
		swap_arr(array, a, z);
		a++;
		z--;
	}
	quicksort_zones(array, start, start + n, cmp);
	quicksort_zones(array, start + n + 1, end, cmp);
}
