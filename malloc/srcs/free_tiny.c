/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tiny.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:51:09 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 15:51:11 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char	is_allocated_tiny_adress(t_malloc_data *data, void *ptr,
							t_tiny_block *start, void **prev_next_block[2])
{
	void	*block;
	void	*end;

	block = (void*)start;
	end = block + (get_tiny_zone_size(data) - sizeof(t_zone));
	write(1, "tiny ? address : ", ft_strlen("tiny ? address : "));
	print_address(ptr);
	write(1, "\n", 1);
	ft_putstr("end : ");
	print_address(end);
	ft_putstr("\n");
	while (block != NULL && block < end)
	{
		*(prev_next_block[1]) = block + ((size_t)((t_tiny_block*)block)->size
													+ sizeof(t_tiny_block));
		write(1, "block : ", 7);
		print_address(block);
		write(1, "\n", 1);
		print_number(((t_tiny_block*)block)->size);
		ft_putstr("\n");
		print_number(get_tiny_zone_size(data));
		ft_putstr("\n");
		if (*(prev_next_block[1]) >= end)
			*(prev_next_block[1]) = NULL;
		if (ptr == (block + sizeof(t_tiny_block)))
			return (1);
		*(prev_next_block[0]) = block;
		block = *(prev_next_block[1]);
	}
	*(prev_next_block[0]) = NULL;
	*(prev_next_block[1]) = NULL;
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
}

void	free_tiny(t_malloc_data *data, void *ptr, void *prev_block,
															void *next_block)
{
	if (((t_tiny_block*)ptr)->free)
		return ;
	print_debug_free_tiny(data, ptr, ((t_tiny_block*)ptr)->size);
	((t_tiny_block*)ptr)->free = 1;
	if (prev_block && ((t_tiny_block*)prev_block)->free == 1)
	{
		if (next_block && ((t_tiny_block*)next_block)->free == 1)
			((t_tiny_block*)prev_block)->size += (sizeof(t_tiny_block) * 2)
			+ ((t_tiny_block*)next_block)->size + ((t_tiny_block*)ptr)->size;
		else
			((t_tiny_block*)prev_block)->size += sizeof(t_tiny_block)
				+ ((t_tiny_block*)ptr)->size;
	}
	else if (next_block && ((t_tiny_block*)next_block)->free == 1)
	{
		((t_tiny_block*)ptr)->size += sizeof(t_tiny_block)
										+ ((t_tiny_block*)next_block)->size;
		change_free_tiny(data, next_block, ptr);
	}
	else
		add_to_list(&(data->free_tiny_blocks), ptr);
}
