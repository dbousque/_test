/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:52:18 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 15:52:19 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		cmp_by_addr(t_sort_zone *elt1, t_sort_zone *elt2)
{
	if (elt1->zone == elt2->zone)
		return (0);
	if (elt1->zone > elt2->zone)
		return (1);
	return (-1);
}

void	print_sort_zones(t_malloc_data *data, t_sort_zone *zones, size_t len)
{
	size_t	i;
	size_t	tot_size;

	tot_size = 0;
	i = 0;
	while (i < len)
	{
		if (zones[i].type == TINY)
			tot_size += print_tiny_zone(data, zones[i].zone);
		if (zones[i].type == SMALL)
			tot_size += print_small_zone(data, zones[i].zone);
		if (zones[i].type == LARGE)
			tot_size += print_raw_zone(zones[i].zone);
		i++;
	}
	write(1, "Total : ", 8);
	print_number(tot_size);
	write(1, " octets\n", 8);
}

void	print_mem(t_malloc_data *data)
{
	t_sort_zone	allocs[data->zones.len + data->raw_blocks.len];
	size_t		i;
	size_t		tmp;

	i = 0;
	while (i < data->zones.len)
	{
		allocs[i].type = ((t_zone*)data->zones.elts[i])->type;
		allocs[i].zone = data->zones.elts[i];
		i++;
	}
	tmp = i;
	while (i - tmp < data->raw_blocks.len)
	{
		allocs[i].type = LARGE;
		allocs[i].zone = data->raw_blocks.elts[i - tmp];
		i++;
	}
	quicksort_zones(allocs, 0, data->zones.len + data->raw_blocks.len,
																cmp_by_addr);
	print_sort_zones(data, allocs, data->zones.len + data->raw_blocks.len);
}

void	dump_hexa(void *ptr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (i != 0 && i % 16 == 0)
			write(1, "\n", 1);
		if (*((char*)ptr + i) < 16)
			write(1, "0", 1);
		print_byte(ptr + i);
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	malloc_dump_hexa(t_malloc_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->zones.len)
	{
		if (((t_zone*)data->zones.elts[i])->type == TINY)
			dump_hexa_tiny(data, data->zones.elts[i]);
		if (((t_zone*)data->zones.elts[i])->type == SMALL)
			dump_hexa_small(data, data->zones.elts[i]);
		i++;
	}
	i = 0;
	while (i < data->raw_blocks.len)
	{
		dump_hexa_raw(data->raw_blocks.elts[i]);
		i++;
	}
}
