/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:54:09 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 16:12:52 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_debug_realloc_small(t_malloc_data *data, void *ptr,
										size_t start_size, size_t end_size)
{
	char	*tmp;

	if (data->debug_print)
	{
		tmp = "Reallocing small block at ";
		write(1, tmp, ft_strlen(tmp));
		print_address(ptr);
		tmp = " of size ";
		write(1, tmp, ft_strlen(tmp));
		print_number(start_size);
		tmp = " to size ";
		write(1, tmp, ft_strlen(tmp));
		print_number(end_size);
		write(1, "\n", 1);
	}
}

void	print_debug_realloc_tiny(t_malloc_data *data, void *ptr,
										size_t start_size, size_t end_size)
{
	char	*tmp;

	if (data->debug_print)
	{
		tmp = "Reallocing tiny block at ";
		write(1, tmp, ft_strlen(tmp));
		print_address(ptr);
		tmp = " of size ";
		write(1, tmp, ft_strlen(tmp));
		print_number(start_size);
		tmp = " to size ";
		write(1, tmp, ft_strlen(tmp));
		print_number(end_size);
		write(1, "\n", 1);
	}
}

void	print_debug_malloc(size_t size, void *ptr)
{
	char	*tmp;

	tmp = "Malloc of size ";
	write(1, tmp, ft_strlen(tmp));
	print_number(size);
	write(1, " : ", 3);
	print_address(ptr);
	write(1, "\n", 1);
}

void	malloc_dump_free(t_malloc_data *data)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (i < data->free_tiny_blocks.len)
	{
		tmp = "free tiny  block of size ";
		write(1, tmp, ft_strlen(tmp));
		print_number(((t_tiny_block*)data->free_tiny_blocks.elts[i])->size);
		write(1, " bytes at ", 10);
		print_address(data->free_tiny_blocks.elts[i] + sizeof(t_tiny_block));
		write(1, "\n", 1);
		i++;
	}
	i = 0;
	while (i < data->free_small_blocks.len)
	{
		tmp = "free small block of size ";
		write(1, tmp, ft_strlen(tmp));
		print_number(((t_small_block*)data->free_small_blocks.elts[i])->size);
		write(1, " bytes at ", 10);
		print_address(data->free_small_blocks.elts[i] + sizeof(t_small_block));
		write(1, "\n", 1);
		i++;
	}
}
