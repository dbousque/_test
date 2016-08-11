/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:53:02 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 16:00:04 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*new_raw(t_malloc_data *data, void *ptr, size_t size)
{
	void	*res;

	res = malloc(size);
	memcopy(ptr, res, *((size_t*)(ptr - (sizeof(size_t)))));
	my_free(data, ptr);
	return (res);
}

void	*realloc_raw(t_malloc_data *data, void *prev_next_blocks[2],
													void *ptr, size_t size)
{
	(void)prev_next_blocks;
	if (data->debug_print)
		print_debug_realloc_raw(ptr,
							*((size_t*)(ptr - (sizeof(size_t)))), size);
	if (data->debug_alloc || size <= MAX_SMALL_BLOCK)
		return (new_raw(data, ptr, size));
	if (*((size_t*)(ptr - (sizeof(size_t) * 2))) - (sizeof(size_t) * 2) >= size)
	{
		*((size_t*)(ptr - (sizeof(size_t)))) = size;
		return (ptr);
	}
	return (new_raw(data, ptr, size));
}

	# include <stdio.h>

void	*my_realloc(t_malloc_data *data, void *ptr, size_t size)
{
	size_t	zone_type;
	void	*prev_next_blocks[2];

	if (!size)
		return (NULL);
	if (!ptr)
		return (my_malloc(data, size));
	prev_next_blocks[0] = NULL;
	prev_next_blocks[1] = NULL;
	ft_putstr("BFORE GET_ZONE\n");
	fflush(stdout);
	zone_type = get_zone_type(data, ptr, &(prev_next_blocks[0]),
													&(prev_next_blocks[1]));
	if (zone_type == 3 || zone_type == 0)
	{
		ft_putstr("RETURNING NULL\n");
		fflush(stdout);
		return (my_malloc(data, size));
	}
	if (zone_type == TINY)
		return (realloc_tiny(data, prev_next_blocks, ptr, size));
	if (zone_type == SMALL)
		return (realloc_small(data, prev_next_blocks, ptr, size));
	else
		return (realloc_raw(data, prev_next_blocks, ptr, size));
}
