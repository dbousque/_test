

#include "malloc.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	get_zone_type(t_malloc_data *data, void *ptr, void **prev_block,
														void **next_block)
{
	size_t	i;
	size_t	tiny_zone_size;
	size_t	small_zone_size;
	void	*start;
	void	**prev_next_block[2];

	prev_next_block[0] = prev_block;
	prev_next_block[1] = next_block;
	tiny_zone_size = get_tiny_zone_size(data);
	small_zone_size = get_small_zone_size(data);
	if (data->zones.len > 0)
	{
		i = data->zones.len - 1;
		while (1)
		{
			start = (void*)(data->zones.elts[i]);
			if (ptr > start)
			{
				if (((t_zone*)start)->type == SMALL
					&& ptr < start + small_zone_size)
					return (is_allocated_small_adress(data, ptr, start
							+ sizeof(t_zone), prev_next_block) ? SMALL : 0);
				if (((t_zone*)start)->type == TINY
					&& ptr < start + tiny_zone_size)
					return (is_allocated_tiny_adress(data, ptr, start
							+ sizeof(t_zone), prev_next_block) ? TINY : 0);
			}
			if (i == 0)
				break ;
			i--;
		}
	}
	return (is_raw_block(data, ptr) + 3);
}

void	memcopy(void *from, void *to, size_t nb)
{
	char	*from_c;
	char	*to_c;

	from_c = (char*)from;
	to_c = (char*)to;
	if (nb == 0)
		return ;
	nb--;
	while (1)
	{
		to_c[nb] = from_c[nb];
		if (nb == 0)
			break ;
		nb--;
	}
}

size_t	ind_of_tiny_block(t_malloc_data *data, void *ptr)
{
	size_t	i;

	i = data->free_tiny_blocks.len;
	while (1)
	{
		if (i == 0)
			break ;
		if (data->free_tiny_blocks.elts[i - 1] == ptr)
			return (i);
		i--;
	}
	return (0);
}

size_t	ind_of_small_block(t_malloc_data *data, void *ptr)
{
	size_t	i;

	i = data->free_small_blocks.len;
	while (1)
	{
		if (i == 0)
			break ;
		if (data->free_small_blocks.elts[i - 1] == ptr)
			return (i);
		i--;
	}
	return (0);
}