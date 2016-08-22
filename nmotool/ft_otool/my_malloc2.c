/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 15:49:12 by dbousque          #+#    #+#             */
/*   Updated: 2016/08/16 15:49:20 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_malloc.h"

void	free_list(t_zone_list *allocs)
{
	int		i;

	if (allocs->size)
	{
		i = 0;
		while (i < allocs->len)
		{
			if (MMAP_MODE)
				my_munmap(allocs->elts[i].start, STD_ALLOC);
			else
				free(allocs->elts[i].start);
			i++;
		}
	}
}

void	double_allocs_size(t_zone_list *allocs, char *error)
{
	t_zone	*new_elts;
	int		i;

	new_elts = MMAP_MODE ? my_mmap(sizeof(t_zone) * (allocs->size * 2))
					: malloc(sizeof(t_zone) * (allocs->size * 2));
	if (!new_elts)
	{
		*error = 1;
		return ;
	}
	i = 0;
	while (i < allocs->len)
	{
		new_elts[i].start = allocs->elts[i].start;
		new_elts[i].current = allocs->elts[i].current;
		new_elts[i].end = allocs->elts[i].end;
		i++;
	}
	if (MMAP_MODE)
		my_munmap(allocs->elts, sizeof(t_zone) * allocs->size);
	else
		free(allocs->elts);
	allocs->elts = new_elts;
	allocs->size *= 2;
}
