

#include "malloc.h"



#   include <stdio.h>

void	small_reduce_size(t_malloc_data *data, t_small_block *block, size_t size,
												void *prev_next_blocks[2])
{
	size_t			res_size;
	t_small_block	*new_block;

	res_size = block->size - size - sizeof(t_small_block);
	if (prev_next_blocks[1]
		&& ((t_small_block*)prev_next_blocks[1])->free == 1)
	{
		remove_free_small_block(data,
			ind_of_small_block(data, prev_next_blocks[1]));
		res_size += ((t_small_block*)prev_next_blocks[1])->size
						+ sizeof(t_small_block);
	}
	new_block = ((t_small_block*)block + sizeof(t_small_block) + size);
	new_block->free = 1;
	new_block->size = res_size;
	add_to_list(&(data->free_small_blocks), new_block);
	block->size = size;
}

void	*realloc_small(t_malloc_data *data, void *prev_next_blocks[2],
													void *ptr, size_t size)
{
	t_small_block	*block;
	t_small_block	*new_block;

	block = ptr - (sizeof(t_small_block));
	if (block->free)
		return (my_malloc(data, size));
	if (size >= block->size - sizeof(t_small_block) && size <= block->size)
		return (ptr);
	if (size < block->size)
	{
		small_reduce_size(data, block, size, prev_next_blocks);
		return (ptr);
	}
	if (prev_next_blocks[1] && ((t_small_block*)prev_next_blocks[1])->free == 1)
	{
		if (((t_small_block*)prev_next_blocks[1])->size >= size - block->size)
		{
			new_block = ((t_small_block*)ptr + size);
			new_block->free = 1;
			new_block->size = ((t_small_block*)prev_next_blocks[1])->size - (size - block->size);
			remove_free_small_block(data, ind_of_small_block(data, prev_next_blocks[1]));
			add_to_list(&(data->free_tiny_blocks), new_block);
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
	void *new = malloc(size);
	memcopy(ptr, new, block->size);
	free_small(data, ptr, prev_next_blocks[0], prev_next_blocks[1]);
	return (new);
}

void	*realloc_tiny(t_malloc_data *data, void *prev_next_blocks[2],
													void *ptr, size_t size)
{
	t_tiny_block	*block;
	t_tiny_block	*new_block;
	size_t			res_size;

	block = ptr - (sizeof(t_tiny_block));
	if (block->free)
		return (my_malloc(data, size));
	if (size >= block->size - sizeof(t_tiny_block) && size <= block->size)
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
			new_block = ((t_tiny_block*)ptr + size);
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
	void *new = malloc(size);
	memcopy(ptr, new, block->size);
	free_tiny(data, ptr, prev_next_blocks[0], prev_next_blocks[1]);
	return (new);
}

void	*realloc_raw(t_malloc_data *data, void *prev_next_blocks[2], void *ptr, size_t size)
{
	void	*res;

	printf("RAW REALLOC\n");
	fflush(stdout);
	(void)prev_next_blocks;
	if (*((size_t*)ptr - (sizeof(size_t) * 2)) >= size)
	{
		*((size_t*)ptr - (sizeof(size_t))) = size;
		return (ptr);
	}
	res = malloc(size);
	memcopy(ptr, res, *((size_t*)ptr - (sizeof(size_t))));
	my_free(data, ptr);
	printf("END OF RAW REALLOC\n");
	fflush(stdout);
	return (res);
}

void	*my_realloc(t_malloc_data *data, void *ptr, size_t size)
{
	size_t	zone_type;
	void	*prev_next_blocks[2];

	if (!ptr)
		return (my_malloc(data, size));
	prev_next_blocks[0] = NULL;
	prev_next_blocks[1] = NULL;
	zone_type = get_zone_type(data, ptr, &(prev_next_blocks[1]), &(prev_next_blocks[0]));
	if (zone_type == 3 || zone_type == 0)
		return (NULL);
	if (zone_type == TINY)
		return (realloc_tiny(data, prev_next_blocks, ptr, size));
	if (zone_type == SMALL)
		return (realloc_small(data, prev_next_blocks, ptr, size));
	else
		return (realloc_raw(data, prev_next_blocks, ptr, size));
}