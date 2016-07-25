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

void	print_debug_malloc(size_t size)
{
	char	*tmp;

	tmp = "Malloc of size ";
	write(1, tmp, ft_strlen(tmp));
	print_number(size);
	write(1, "\n", 1);
}
