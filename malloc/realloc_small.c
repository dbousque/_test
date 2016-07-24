

#include "malloc.h"

void	*new_small(t_malloc_data *data, void *ptr,
									void *prev_next_blocks[2], size_t size)
{
	void			*new;
	t_small_block	*block;

	block = (t_small_block*)(ptr - (sizeof(t_small_block)));
	new = malloc(size);
	memcopy(ptr, new, block->size);
	free_small(data, block, prev_next_blocks[0], prev_next_blocks[1]);
	return (new);
}

void	*reduce_small_size(t_malloc_data *data, void *ptr,
					void *prev_next_blocks[2], size_t size)
{
	size_t			res_size;
	t_small_block	*block;
	t_small_block	*new_block;

	block = (t_small_block*)(ptr - (sizeof(t_small_block)));
	res_size = block->size - size - sizeof(t_small_block);
	if (prev_next_blocks[1]
		&& ((t_small_block*)prev_next_blocks[1])->free == 1)
	{
		remove_free_small_block(data,
							ind_of_small_block(data, prev_next_blocks[1]));
		res_size += ((t_small_block*)prev_next_blocks[1])->size
										+ sizeof(t_small_block);
	}
	new_block = ((t_small_block*)ptr + size);
	new_block->free = 1;
	new_block->size = res_size;
	add_to_list(&(data->free_small_blocks), new_block);
	block->size = size;
	return (ptr);
}

void	*resize_small_greater(t_malloc_data *data, void *ptr,
								void *prev_next_blocks[2], size_t size)
{
	t_small_block	*new_block;
	t_small_block	*block;

	block = (t_small_block*)(ptr - (sizeof(t_small_block)));
	new_block = ((t_small_block*)(ptr + size));
	new_block->free = 1;
	new_block->size = ((t_small_block*)prev_next_blocks[1])->size
													- (size - block->size);
	remove_free_small_block(data,
							ind_of_small_block(data, prev_next_blocks[1]));
	add_to_list(&(data->free_small_blocks), new_block);
	block->size = size;
	return (ptr);
}

void	*realloc_small(t_malloc_data *data, void *p_nx_b[2],
													void *ptr, size_t size)
{
	t_small_block	*blo;

	blo = (t_small_block*)(ptr - (sizeof(t_small_block)));
	if (blo->free)
		return (NULL);
	print_debug_realloc_small(data, ptr, blo->size, size);
	if (size > MAX_SMALL_BLOCK || size <= MAX_TINY_BLOCK)
		return (new_small(data, ptr, p_nx_b, size));
	if (size >= blo->size - ((int)sizeof(t_small_block)) && size <= blo->size)
		return (ptr);
	if (size < blo->size)
		return (reduce_small_size(data, ptr, p_nx_b, size));
	if (p_nx_b[1] && ((t_small_block*)p_nx_b[1])->free == 1)
	{
		if (((t_small_block*)p_nx_b[1])->size >= size - blo->size)
			return (resize_small_greater(data, ptr, p_nx_b, size));
		else if (((t_small_block*)p_nx_b[1])->size
							+ sizeof(t_small_block) >= size - blo->size)
		{
			blo->size += ((t_small_block*)p_nx_b[1])->size
												+ sizeof(t_small_block);
			remove_free_small_block(data, ind_of_small_block(data, p_nx_b[1]));
			return (ptr);
		}
	}
	return (new_small(data, ptr, p_nx_b, size));
}