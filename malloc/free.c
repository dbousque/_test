

#include "malloc.h"

size_t	is_raw_block(t_malloc_data *data, void *ptr)
{
	size_t	i;

	if (!data->raw_blocks.elts || data->raw_blocks.len == 0)
		return (0);
	i = data->raw_blocks.len - 1;
	while (1)
	{
		if ((data->raw_blocks.elts[i] + (sizeof(size_t) * 2)) == ptr)
			return (i + 1);
		if (i == 0)
			break ;
		i--;
	}
	return (0);
}

void	free_raw_block(t_malloc_data *data, size_t ind)
{
	size_t	i;

	if (data->debug_print)
		print_debug_free_raw(data->raw_blocks.elts[ind],
							*((size_t*)(data->raw_blocks.elts[ind] + sizeof(size_t))));
	my_munmap(data->raw_blocks.elts[ind],
								*((size_t*)(data->raw_blocks.elts[ind])));
	data->raw_blocks.elts[ind] = NULL;
	i = ind + 1;
	while (i < data->raw_blocks.len)
	{
		data->raw_blocks.elts[i - 1] = data->raw_blocks.elts[i];
		i++;
	}
	data->raw_blocks.len--;
}

void	my_free(t_malloc_data *data, void *ptr)
{
	size_t	zone_type;
	void	*prev_block;
	void	*next_block;

	if (!ptr)
	{
		if (data->debug_print)
			print_debug_free_null();
		return ;
	}
	prev_block = NULL;
	next_block = NULL;
	zone_type = get_zone_type(data, ptr, &prev_block, &next_block);
	if (zone_type == 3 || zone_type == 0)
		return ;
	if (zone_type == TINY)
		free_tiny(data, (ptr - sizeof(t_tiny_block)), prev_block, next_block);
	else if (zone_type == SMALL)
		free_small(data, (ptr - sizeof(t_small_block)),
													prev_block, next_block);
	else
		free_raw_block(data, zone_type - 4);
}