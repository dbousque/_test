/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_malloc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:52:24 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 15:52:26 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	print_stuff_tiny(void *block, size_t tot_size, void *zone)
{
	char	*tmp;

	if (tot_size == 0)
	{
		tmp = "TINY : ";
		write(1, tmp, ft_strlen(tmp));
		print_address(zone);
		write(1, "\n", 1);
	}
	tot_size += ((t_tiny_block*)block)->size;
	print_address(block + sizeof(t_tiny_block));
	write(1, " - ", 3);
	print_address(block + sizeof(t_tiny_block)
								+ ((size_t)((t_tiny_block*)block)->size));
	write(1, " : ", 3);
	print_number(((t_tiny_block*)block)->size);
	write(1, " octets\n", 8);
	return (tot_size);
}

size_t	print_tiny_zone(t_malloc_data *data, void *zone)
{
	void	*block;
	void	*end;
	void	*tmp_bl;
	size_t	tot_size;

	tot_size = 0;
	block = (void*)zone + sizeof(t_zone);
	end = block + (get_tiny_zone_size(data) - sizeof(t_zone));
	while (block != NULL && block < end)
	{
		if (((t_tiny_block*)block)->free == 0)
			tot_size = print_stuff_tiny(block, tot_size, zone);
		tmp_bl = block + ((size_t)((t_tiny_block*)block)->size
													+ sizeof(t_tiny_block));
		if (tmp_bl < block)
			break ;
		block = tmp_bl;
	}
	return (tot_size);
}

size_t	print_stuff_small(void *block, size_t tot_size, void *zone)
{
	char	*tmp;

	if (tot_size == 0)
	{
		tmp = "SMALL : ";
		write(1, tmp, ft_strlen(tmp));
		print_address(zone);
		write(1, "\n", 1);
	}
	tot_size += ((t_small_block*)block)->size;
	print_address(block + sizeof(t_small_block));
	write(1, " - ", 3);
	print_address(block + sizeof(t_small_block)
								+ ((size_t)((t_small_block*)block)->size));
	write(1, " : ", 3);
	print_number(((t_small_block*)block)->size);
	write(1, " octets\n", 8);
	return (tot_size);
}

size_t	print_small_zone(t_malloc_data *data, void *zone)
{
	void	*block;
	void	*end;
	void	*tmp_bl;
	size_t	tot_size;

	tot_size = 0;
	block = (void*)zone + sizeof(t_zone);
	end = block + (get_small_zone_size(data) - sizeof(t_zone));
	while (block != NULL && block < end)
	{
		if (((t_small_block*)block)->free == 0)
			tot_size = print_stuff_small(block, tot_size, zone);
		tmp_bl = block + ((size_t)((t_small_block*)block)->size
													+ sizeof(t_small_block));
		if (tmp_bl < block)
			break ;
		block = tmp_bl;
	}
	return (tot_size);
}

size_t	print_raw_zone(void *zone)
{
	char	*tmp;
	size_t	size;

	tmp = "LARGE : ";
	write(1, tmp, ft_strlen(tmp));
	print_address(zone);
	write(1, "\n", 1);
	print_address(zone + (sizeof(size_t) * 2));
	write(1, " - ", 3);
	size = *((size_t*)(zone + sizeof(size_t)));
	print_address(zone + (sizeof(size_t) * 2) + size);
	write(1, " : ", 3);
	print_number(size);
	write(1, " octets\n", 8);
	return (size);
}
