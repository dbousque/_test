/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tiny.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:50:51 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 15:56:54 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				add_new_tiny_zone(t_malloc_data *data)
{
	t_zone	*new_zone;
	size_t	alloc_size;

	alloc_size = get_tiny_zone_size(data);
	new_zone = (t_zone*)my_mmap(alloc_size);
	if (!new_zone)
		return (0);
	new_zone->type = TINY;
	add_to_list(&(data->zones), new_zone);
	add_new_free_tiny_block(data, ((void*)new_zone) + sizeof(t_zone),
		alloc_size - sizeof(t_zone) - sizeof(t_tiny_block));
	ft_putstr("NEW ZONE TINY SIZE FOR FREE BLOCK : ");
	print_number(alloc_size - sizeof(t_zone) - sizeof(t_tiny_block));
	ft_putstr("\n");
	return (1);
}

size_t			select_free_tiny_block(t_malloc_data *data, size_t size,
															int *error)
{
	size_t	i;

	if (data->free_tiny_blocks.len > 0)
	{
		i = data->free_tiny_blocks.len - 1;
		while (1)
		{
			ft_putstr("\nfree size : ");
			print_number(((t_tiny_block*)data->free_tiny_blocks.elts[i])->size);
			ft_putstr("\n");
			ft_putstr("is_free : ");
			if (((t_tiny_block*)data->free_tiny_blocks.elts[i])->free)
				ft_putstr("true\n");
			else
				ft_putstr("false\n");
			if (((t_tiny_block*)data->free_tiny_blocks.elts[i])->size >= size)
				return (i);
			if (i == 0)
				break ;
			i--;
		}
	}
	if (!add_new_tiny_zone(data))
		*error = 1;
	return (data->free_tiny_blocks.len - 1);
}

void			remove_free_tiny_block(t_malloc_data *data, size_t ind)
{
	size_t	i;

	i = ind + 1;
	while (i < data->free_tiny_blocks.len)
	{
		data->free_tiny_blocks.elts[i - 1] = data->free_tiny_blocks.elts[i];
		i++;
	}
	data->free_tiny_blocks.len--;
}

t_tiny_block	*alloc_tiny_block_for_use(t_malloc_data *data, size_t size,
																	size_t ind)
{
	t_tiny_block	*block;
	t_tiny_block	*new_free_block;
	char			new_free;

	new_free = 0;
	block = ((t_tiny_block*)(data->free_tiny_blocks.elts[ind]));
	ft_putstr("selected block address : ");
	print_address(block);
	ft_putstr("\n");

	ft_putstr("NEW SIZES : ");
	print_number(block->size);
	ft_putstr(" ; ");
	print_number(((block->size - (size + sizeof(t_tiny_block)))));

	if (block->size > size + (sizeof(t_tiny_block) * 2))
	{
		new_free_block = (void*)block + size + sizeof(t_tiny_block);
		new_free_block->size = block->size - size - sizeof(t_tiny_block);
		new_free_block->free = 1;
		new_free = 1;
		block->size = size;
	}
	block->free = 0;
	if (new_free)
	{
		ft_putstr("NEW FREE, block : ");
		print_address(block);
		ft_putstr(" ; new_block : ");
		print_address(new_free_block);
		ft_putstr("\n");
		data->free_tiny_blocks.elts[ind] = new_free_block;
	}
	else
	{
		ft_putstr("REMOVING\n");
		remove_free_tiny_block(data, ind);
	}
	return (((void*)block) + sizeof(t_tiny_block));
}

void			*alloc_tiny(t_malloc_data *data, size_t size)
{
	size_t	selected_ind;
	int		error;

	error = 0;
	if (!data->free_tiny_blocks.elts)
	{
		data->free_tiny_blocks.size = getpagesize() / sizeof(void*);
		data->free_tiny_blocks.len = 0;
		data->free_tiny_blocks.elts = (void**)my_mmap(sizeof(void*)
											* data->free_tiny_blocks.size);
		if (!data->free_tiny_blocks.elts)
			return (NULL);
		if (!add_new_tiny_zone(data))
			return (NULL);
	}
	selected_ind = select_free_tiny_block(data, size, &error);
	if (error)
		return (NULL);
	return (alloc_tiny_block_for_use(data, size, selected_ind));
}
