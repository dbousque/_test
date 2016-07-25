/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_small.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:50:44 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 15:56:45 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				add_new_small_zone(t_malloc_data *data)
{
	t_zone	*new_zone;
	size_t	alloc_size;

	alloc_size = get_small_zone_size(data);
	new_zone = (t_zone*)my_mmap(alloc_size);
	if (!new_zone)
		return (0);
	new_zone->type = SMALL;
	add_to_list(&(data->zones), new_zone);
	add_new_free_small_block(data, (void*)new_zone + sizeof(t_zone),
		alloc_size - sizeof(t_zone) - sizeof(t_small_block));
	return (1);
}

size_t			select_free_small_block(t_malloc_data *data, size_t size,
															int *error)
{
	size_t	i;

	if (data->free_small_blocks.len > 0)
	{
		i = data->free_small_blocks.len - 1;
		while (1)
		{
			if (((t_small_block*)data->free_small_blocks.elts[i])->size >=
												size + sizeof(t_small_block))
				return (i);
			if (i == 0)
				break ;
			i--;
		}
	}
	if (!add_new_small_zone(data))
		*error = 1;
	return (data->free_small_blocks.len - 1);
}

void			remove_free_small_block(t_malloc_data *data, size_t ind)
{
	size_t	i;

	i = ind + 1;
	while (i < data->free_small_blocks.len)
	{
		data->free_small_blocks.elts[i - 1] = data->free_small_blocks.elts[i];
		i++;
	}
	data->free_small_blocks.len--;
}

t_small_block	*alloc_small_block_for_use(t_malloc_data *data, size_t size,
																	size_t ind)
{
	t_small_block	*block;
	t_small_block	*new_free_block;
	char			new_free;

	new_free = 0;
	block = ((t_small_block*)data->free_small_blocks.elts[ind]);
	if (block->size > size + (sizeof(t_small_block) * 2))
	{
		new_free_block = (void*)block + size + sizeof(t_small_block);
		new_free_block->size = block->size - size - sizeof(t_small_block);
		new_free_block->free = 1;
		new_free = 1;
	}
	block->size = size;
	block->free = 0;
	if (new_free)
		data->free_small_blocks.elts[ind] = new_free_block;
	else
		remove_free_small_block(data, ind);
	return ((void*)block + sizeof(t_small_block));
}

void			*alloc_small(t_malloc_data *data, size_t size)
{
	size_t	selected_ind;
	int		error;

	error = 0;
	if (!data->free_small_blocks.elts)
	{
		data->free_small_blocks.size = getpagesize() / sizeof(void*);
		data->free_small_blocks.len = 0;
		data->free_small_blocks.elts = (void**)my_mmap(sizeof(void*)
											* data->free_small_blocks.size);
		if (!data->free_small_blocks.elts)
			return (NULL);
		if (!add_new_small_zone(data))
			return (NULL);
	}
	selected_ind = select_free_small_block(data, size, &error);
	if (error)
		return (NULL);
	return (alloc_small_block_for_use(data, size, selected_ind));
}
