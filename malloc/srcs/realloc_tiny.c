/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tiny.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:53:10 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 16:43:45 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*new_tiny(t_malloc_data *data, void *ptr,
									void *prev_next_blocks[2], size_t size)
{
	void			*new;
	t_tiny_block	*block;

	block = (t_tiny_block*)(ptr - (sizeof(t_tiny_block)));
	new = my_malloc(data, size);
	memcopy(ptr, new, block->size);
	free_tiny(data, block, prev_next_blocks[0], prev_next_blocks[1]);
	return (new);
}

void	*reduce_tiny_size(t_malloc_data *data, void *ptr,
					void *prev_next_blocks[2], size_t size)
{
	size_t			res_size;
	t_tiny_block	*block;
	t_tiny_block	*new_block;

	block = (t_tiny_block*)(ptr - (sizeof(t_tiny_block)));
	res_size = block->size - size - sizeof(t_tiny_block);
	if (prev_next_blocks[1]
		&& ((t_tiny_block*)prev_next_blocks[1])->free == 1)
	{
		remove_free_tiny_block(data,
							ind_of_tiny_block(data, prev_next_blocks[1]));
		res_size += ((t_tiny_block*)prev_next_blocks[1])->size
										+ sizeof(t_tiny_block);
	}
	new_block = ((t_tiny_block*)ptr + size);
	new_block->free = 1;
	new_block->size = res_size;
	add_to_list(&(data->free_tiny_blocks), new_block);
	block->size = size;
	return (ptr);
}

void	*resize_tiny_greater(t_malloc_data *data, void *ptr,
								void *prev_next_blocks[2], size_t size)
{
	t_tiny_block	*new_block;
	t_tiny_block	*block;

	block = (t_tiny_block*)(ptr - (sizeof(t_tiny_block)));
	new_block = ((t_tiny_block*)(ptr + size));
	new_block->free = 1;
	new_block->size = ((t_tiny_block*)prev_next_blocks[1])->size
													- (size - block->size);
	remove_free_tiny_block(data, ind_of_tiny_block(data, prev_next_blocks[1]));
	add_to_list(&(data->free_tiny_blocks), new_block);
	block->size = size;
	return (ptr);
}

void	*realloc_tiny(t_malloc_data *data, void *p_nx_b[2],
													void *ptr, size_t size)
{
	t_tiny_block	*b;

	b = (t_tiny_block*)(ptr - (sizeof(t_tiny_block)));
	if (b->free)
		return (NULL);
	print_debug_realloc_tiny(data, ptr, b->size, size);
	if (size > MAX_TINY_BLOCK)
		return (new_tiny(data, ptr, p_nx_b, size));
	if (size >= b->size - ((int)sizeof(t_tiny_block)) && size <= b->size)
		return (ptr);
	if (size < b->size)
		return (reduce_tiny_size(data, ptr, p_nx_b, size));
	if (p_nx_b[1] && ((t_tiny_block*)p_nx_b[1])->free == 1)
	{
		if (((t_tiny_block*)p_nx_b[1])->size >= size - b->size)
			return (resize_tiny_greater(data, ptr, p_nx_b, size));
		else if (((t_tiny_block*)p_nx_b[1])->size
							+ sizeof(t_tiny_block) >= size - b->size)
		{
			b->size += ((t_tiny_block*)p_nx_b[1])->size + sizeof(t_tiny_block);
			remove_free_tiny_block(data, ind_of_tiny_block(data, p_nx_b[1]));
			return (ptr);
		}
	}
	return (new_tiny(data, ptr, p_nx_b, size));
}
