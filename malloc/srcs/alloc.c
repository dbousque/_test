/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:50:20 by dbousque          #+#    #+#             */
/*   Updated: 2016/08/15 14:33:56 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	add_new_free_tiny_block(t_malloc_data *data, void *start, size_t size)
{
	t_tiny_block	*block;

	block = (t_tiny_block*)start;
	block->size = (uint16_t)size;
	block->free = 1;
	add_to_list(&(data->free_tiny_blocks), block);
}

void	add_new_free_small_block(t_malloc_data *data, void *start, size_t size)
{
	t_small_block	*block;

	block = (t_small_block*)start;
	block->size = (uint32_t)size;
	block->free = 1;
	add_to_list(&(data->free_small_blocks), block);
}

void	*get_raw_block(t_malloc_data *data, size_t size)
{
	size_t	block_size;
	void	*ptr;
	size_t	*ptr_t;

	size += (sizeof(size_t) * 2);
	block_size = get_next_pagesize(size);
	ptr = my_mmap(block_size);
	if (!ptr)
		return (NULL);
	ptr_t = (size_t*)ptr;
	*ptr_t = block_size;
	ptr_t = (size_t*)(ptr + sizeof(size_t));
	*ptr_t = size - (sizeof(size_t) * 2);
	add_to_list(&(data->raw_blocks), ptr);
	return (ptr + (sizeof(size_t) * 2));
}

void	*alloc_new_block(t_malloc_data *data, size_t size)
{
	void			*block;

	if (!(data->debug_alloc) && size <= MAX_TINY_BLOCK)
		block = alloc_tiny(data, size);
	else if (!(data->debug_alloc) && size <= MAX_SMALL_BLOCK)
		block = alloc_small(data, size);
	else
	{
		if (!data->raw_blocks.elts)
		{
			data->raw_blocks.size = getpagesize() / sizeof(void*);
			data->raw_blocks.len = 0;
			data->raw_blocks.elts = (void**)my_mmap(sizeof(void*)
												* data->raw_blocks.size);
			if (!data->raw_blocks.elts)
				return (NULL);
		}
		block = get_raw_block(data, size);
	}
	return (block);
}
