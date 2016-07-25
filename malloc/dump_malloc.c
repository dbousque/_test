/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:51:00 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 15:51:02 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_dump_tiny(void *block)
{
	char	*tmp;

	tmp = "TINY at ";
	write(1, tmp, ft_strlen(tmp));
	print_address(block + sizeof(t_tiny_block));
	write(1, "\n", 1);
	dump_hexa(block + sizeof(t_tiny_block), ((t_tiny_block*)block)->size);
}

void	dump_hexa_tiny(t_malloc_data *data, void *zone)
{
	void	*block;
	void	*end;
	void	*tmp_bl;

	block = (void*)zone + sizeof(t_zone);
	end = block + (get_tiny_zone_size(data) - sizeof(t_zone));
	while (block != NULL && block < end)
	{
		if (((t_tiny_block*)block)->free == 0)
			print_dump_tiny(block);
		tmp_bl = block + ((size_t)((t_tiny_block*)block)->size
													+ sizeof(t_tiny_block));
		if (tmp_bl < block)
			break ;
		block = tmp_bl;
	}
}

void	print_dump_small(void *block)
{
	char	*tmp;

	tmp = "SMALL at ";
	write(1, tmp, ft_strlen(tmp));
	print_address(block + sizeof(t_small_block));
	write(1, "\n", 1);
	dump_hexa(block + sizeof(t_small_block), ((t_small_block*)block)->size);
}

void	dump_hexa_small(t_malloc_data *data, void *zone)
{
	void	*block;
	void	*end;
	void	*tmp_bl;

	block = (void*)zone + sizeof(t_zone);
	end = block + (get_small_zone_size(data) - sizeof(t_zone));
	while (block != NULL && block < end)
	{
		if (((t_small_block*)block)->free == 0)
			print_dump_small(block);
		tmp_bl = block + ((size_t)((t_small_block*)block)->size
													+ sizeof(t_small_block));
		if (tmp_bl < block)
			break ;
		block = tmp_bl;
	}
}

void	dump_hexa_raw(void *zone)
{
	char	*tmp;

	tmp = "LARGE at ";
	write(1, tmp, ft_strlen(tmp));
	print_address(zone + (sizeof(size_t) * 2));
	write(1, "\n", 1);
	dump_hexa(zone + (sizeof(size_t) * 2), *((size_t*)(zone + sizeof(size_t))));
}
