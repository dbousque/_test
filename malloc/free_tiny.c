

#include "malloc.h"

char	is_allocated_tiny_adress(t_malloc_data *data, void *ptr,
							t_tiny_block *start, void **prev_next_block[2])
{
	void	*block;
	void	*end;

	block = (void*)start;
	end = block + (get_tiny_zone_size(data) - sizeof(t_zone));
	while (block != NULL && block < end)
	{
		*(prev_next_block[1]) = block + ((size_t)((t_tiny_block*)block)->size
													+ sizeof(t_tiny_block));
		if (*(prev_next_block[1]) >= end)
			*(prev_next_block[1]) = NULL;
		if (ptr == (block + sizeof(t_tiny_block)))
			return (1);
		*(prev_next_block[0]) = block;
		block = *(prev_next_block[1]);
	}
	return (0);
}

void	change_free_tiny(t_malloc_data *data, void *from, void *to)
{
	size_t	i;

	i = data->free_tiny_blocks.len - 1;
	while (1)
	{
		if (data->free_tiny_blocks.elts[i] == from)
		{
			data->free_tiny_blocks.elts[i] = to;
			return ;
		}
		if (i == 0)
			break ;
		i--;
	}
	write(1, "COULD NOT CHANGE TINY\n", ft_strlen("COULD NOT CHANGE TINY\n"));
}

void	free_tiny(t_malloc_data *data, void *ptr, void *prev_block,
															void *next_block)
{
	char	next_block_free;
	char	prev_block_free;

	if (((t_tiny_block*)ptr)->free)
		return ;
	print_debug_free_tiny(data, ptr, ((t_tiny_block*)ptr)->size);
	next_block_free = next_block && ((t_tiny_block*)next_block)->free == 1;
	prev_block_free = prev_block && ((t_tiny_block*)prev_block)->free == 1;
	((t_tiny_block*)ptr)->free = 1;
	if (prev_block_free)
	{
		if (next_block_free)
			((t_tiny_block*)prev_block)->size += (sizeof(t_tiny_block) * 2)
			+ ((t_tiny_block*)next_block)->size + ((t_tiny_block*)ptr)->size;
		else
			((t_tiny_block*)prev_block)->size += sizeof(t_tiny_block)
				+ ((t_tiny_block*)ptr)->size;
	}
	else if (next_block_free)
	{
		((t_tiny_block*)ptr)->size += sizeof(t_tiny_block)
										+ ((t_tiny_block*)next_block)->size;
		change_free_tiny(data, next_block, ptr);
	}
	else
		add_to_list(&(data->free_tiny_blocks), ptr);
}