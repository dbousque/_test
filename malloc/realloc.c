

#include "malloc.h"



#   include <stdio.h>


#  include <stdlib.h>

void	*new_small(t_malloc_data *data, void *ptr,
									void *prev_next_blocks[2], size_t size)
{
	void 			*new;
	t_small_block	*block;

	block = (t_small_block*)(ptr - (sizeof(t_small_block)));
	new = malloc(size);
	memcopy(ptr, new, block->size);
	free_small(data, block, prev_next_blocks[0], prev_next_blocks[1]);
	return (new);
}

void	*realloc_small(t_malloc_data *data, void *prev_next_blocks[2],
													void *ptr, size_t size)
{
	t_small_block	*block;
	t_small_block	*new_block;
	size_t			res_size;

	block = (t_small_block*)(ptr - (sizeof(t_small_block)));
	if (block->free)
		return (NULL);
	if (size > MAX_SMALL_BLOCK || size <= MAX_TINY_BLOCK)
		return (new_small(data, ptr, prev_next_blocks, size));
	if (size >= block->size - ((int)sizeof(t_small_block)) && size <= block->size)
		return (ptr);
	if (size < block->size)
	{
		res_size = block->size - size - sizeof(t_small_block);
		if (prev_next_blocks[1] && ((t_small_block*)prev_next_blocks[1])->free == 1)
		{
			remove_free_small_block(data, ind_of_small_block(data, prev_next_blocks[1]));
			res_size += ((t_small_block*)prev_next_blocks[1])->size + sizeof(t_small_block);
		}
		new_block = ((t_small_block*)ptr + size);
		new_block->free = 1;
		new_block->size = res_size;
		add_to_list(&(data->free_small_blocks), new_block);
		block->size = size;
		return (ptr);
	}
	if (prev_next_blocks[1] && ((t_small_block*)prev_next_blocks[1])->free == 1)
	{
		if (((t_small_block*)prev_next_blocks[1])->size >= size - block->size)
		{
			new_block = ((t_small_block*)(ptr + size));
			new_block->free = 1;
			new_block->size = ((t_small_block*)prev_next_blocks[1])->size - (size - block->size);
			remove_free_small_block(data, ind_of_small_block(data, prev_next_blocks[1]));
			add_to_list(&(data->free_small_blocks), new_block);
			block->size = size;
			return (ptr);
		}
		else if (((t_small_block*)prev_next_blocks[1])->size + sizeof(t_small_block) >= size - block->size)
		{
			block->size += ((t_small_block*)prev_next_blocks[1])->size + sizeof(t_small_block);
			remove_free_small_block(data, ind_of_small_block(data, prev_next_blocks[1]));
			return (ptr);
		}
	}
	return (new_small(data, ptr, prev_next_blocks, size));
}

void	*new_tiny(t_malloc_data *data, void *ptr,
									void *prev_next_blocks[2], size_t size)
{
	void 			*new;
	t_tiny_block	*block;

	block = (t_tiny_block*)(ptr - (sizeof(t_tiny_block)));
	new = malloc(size);
	memcopy(ptr, new, block->size);
	free_tiny(data, block, prev_next_blocks[0], prev_next_blocks[1]);
	return (new);
}

void	*realloc_tiny(t_malloc_data *data, void *prev_next_blocks[2],
													void *ptr, size_t size)
{
	t_tiny_block	*block;
	t_tiny_block	*new_block;
	size_t			res_size;

	block = (t_tiny_block*)(ptr - (sizeof(t_tiny_block)));
	if (block->free)
		return (NULL);
	if (size > MAX_TINY_BLOCK)
	{
		return (new_tiny(data, ptr, prev_next_blocks, size));
	}
	if (size >= block->size - ((int)sizeof(t_tiny_block)) && size <= block->size)
		return (ptr);
	if (size < block->size)
	{
		res_size = block->size - size - sizeof(t_tiny_block);
		if (prev_next_blocks[1] && ((t_tiny_block*)prev_next_blocks[1])->free == 1)
		{
			remove_free_tiny_block(data, ind_of_tiny_block(data, prev_next_blocks[1]));
			res_size += ((t_tiny_block*)prev_next_blocks[1])->size + sizeof(t_tiny_block);
		}
		new_block = ((t_tiny_block*)ptr + size);
		new_block->free = 1;
		new_block->size = res_size;
		add_to_list(&(data->free_tiny_blocks), new_block);
		block->size = size;
		return (ptr);
	}
	if (prev_next_blocks[1] && ((t_tiny_block*)prev_next_blocks[1])->free == 1)
	{
		if (((t_tiny_block*)prev_next_blocks[1])->size >= size - block->size)
		{
			new_block = ((t_tiny_block*)(ptr + size));
			new_block->free = 1;
			new_block->size = ((t_tiny_block*)prev_next_blocks[1])->size - (size - block->size);
			remove_free_tiny_block(data, ind_of_tiny_block(data, prev_next_blocks[1]));
			add_to_list(&(data->free_tiny_blocks), new_block);
			block->size = size;
			return (ptr);
		}
		else if (((t_tiny_block*)prev_next_blocks[1])->size + sizeof(t_tiny_block) >= size - block->size)
		{
			block->size += ((t_tiny_block*)prev_next_blocks[1])->size + sizeof(t_tiny_block);
			remove_free_tiny_block(data, ind_of_tiny_block(data, prev_next_blocks[1]));
			return (ptr);
		}
	}
	return (new_tiny(data, ptr, prev_next_blocks, size));
}

void	*new_raw(t_malloc_data *data, void *ptr, size_t size)
{
	void 			*res;

	res = malloc(size);
	memcopy(ptr, res, *((size_t*)(ptr - (sizeof(size_t)))));
	my_free(data, ptr);
	return (res);
}

void	*realloc_raw(t_malloc_data *data, void *prev_next_blocks[2], void *ptr, size_t size)
{
	(void)prev_next_blocks;
	if (size <= MAX_SMALL_BLOCK)
		return (new_raw(data, ptr, size));
	if (*((size_t*)(ptr - (sizeof(size_t) * 2))) - (sizeof(size_t) * 2) >= size)
	{
		*((size_t*)(ptr - (sizeof(size_t)))) = size;
		return (ptr);
	}
	return (new_raw(data, ptr, size));
}

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
	zone_type = get_zone_type(data, ptr, &(prev_next_blocks[0]), &(prev_next_blocks[1]));
	if (zone_type == 3 || zone_type == 0)
		return (NULL);
	if (zone_type == TINY)
		return (realloc_tiny(data, prev_next_blocks, ptr, size));
	if (zone_type == SMALL)
		return (realloc_small(data, prev_next_blocks, ptr, size));
	else
		return (realloc_raw(data, prev_next_blocks, ptr, size));
}