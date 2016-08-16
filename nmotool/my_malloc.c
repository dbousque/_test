/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 15:49:30 by dbousque          #+#    #+#             */
/*   Updated: 2016/08/16 15:49:32 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_malloc.h"

char	alloc_new_zone(t_zone_list *allocs)
{
	char	error;

	error = 0;
	if (allocs->len == allocs->size)
		double_allocs_size(allocs, &error);
	if (error || !(allocs->elts[allocs->len].start =
						MMAP_MODE ? my_mmap(STD_ALLOC) : malloc(STD_ALLOC)))
		return (0);
	allocs->elts[allocs->len].current = allocs->elts[allocs->len].start;
	allocs->elts[allocs->len].end = allocs->elts[allocs->len].start + STD_ALLOC;
	allocs->len++;
	return (1);
}

void	*malloc_list(t_zone_list *allocs, size_t size)
{
	if (!allocs->size)
	{
		allocs->elts = MMAP_MODE ? my_mmap(sizeof(t_zone) * STD_NB_ZONES)
							: malloc(sizeof(t_zone) * STD_NB_ZONES);
		if (!allocs->elts)
			return (NULL);
		allocs->len = 0;
		allocs->size = STD_NB_ZONES;
	}
	if (allocs->len > 0 && allocs->elts[allocs->len - 1].current
						+ size < allocs->elts[allocs->len - 1].end)
	{
		allocs->elts[allocs->len - 1].current += size;
		return (allocs->elts[allocs->len - 1].current - size);
	}
	while (!(alloc_new_zone(allocs)))
		continue ;
	return (malloc_list(allocs, size));
}

void	*handle_malloc(char option, size_t size)
{
	static t_zone_list	allocs = {NULL, 0, 0};

	if (option == MALLOC)
		return (malloc_list(&allocs, size));
	else if (option == FREE)
		free_list(&allocs);
	return (NULL);
}

void	*my_malloc(size_t size)
{
	//return (malloc(size));
	return (handle_malloc(MALLOC, size));
}

void	free_all(void)
{
	handle_malloc(FREE, 0);
}
