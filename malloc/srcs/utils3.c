/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:53:54 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 16:44:13 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char	get_zone_type_ifs(void *ptr, void *start, t_malloc_data *data,
													void **prev_next_block[2])
{
	size_t	small_zone_size;
	size_t	tiny_zone_size;

	tiny_zone_size = get_tiny_zone_size(data);
	small_zone_size = get_small_zone_size(data);
	if (ptr > start)
	{
		if (((t_zone*)start)->type == SMALL
			&& ptr < start + small_zone_size)
		{
			return (is_allocated_small_adress(data, ptr, start
						+ sizeof(t_zone), prev_next_block) ? SMALL : 0);
		}
		if (((t_zone*)start)->type == TINY
			&& ptr < start + tiny_zone_size)
		{
			return (is_allocated_tiny_adress(data, ptr, start
						+ sizeof(t_zone), prev_next_block) ? TINY : 0);
		}
	}
	return (-1);
}

size_t	get_zone_type(t_malloc_data *data, void *ptr, void **prev_block,
														void **next_block)
{
	size_t	i;
	void	*start;
	void	**prev_next_block[2];
	char	res;

	prev_next_block[0] = prev_block;
	prev_next_block[1] = next_block;
	if (data->zones.len > 0)
	{
		i = data->zones.len - 1;
		while (1)
		{
			start = (void*)(data->zones.elts[i]);
			ft_putstr("zone start : ");
			print_address(start);
			ft_putstr("\n");
			res = get_zone_type_ifs(ptr, start, data, prev_next_block);
			if (res != -1)
				return (res);
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
