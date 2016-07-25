/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:53:48 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 15:53:50 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	get_tiny_zone_size(t_malloc_data *data)
{
	size_t	alloc_size;

	alloc_size = NB_PAGES_PER_TINY_ZONE * data->page_size;
	while (alloc_size < MAX_TINY_BLOCK * 100)
		alloc_size *= 2;
	return (alloc_size);
}

size_t	get_small_zone_size(t_malloc_data *data)
{
	size_t	alloc_size;

	alloc_size = NB_PAGES_PER_SMALL_ZONE * data->page_size;
	while (alloc_size < MAX_SMALL_BLOCK * 100)
		alloc_size *= 2;
	return (alloc_size);
}

void	*my_malloc(t_malloc_data *data, size_t size)
{
	void	*ptr;

	if (!size)
		return (NULL);
	if (data->debug_print)
		print_debug_malloc(size);
	ptr = alloc_new_block(data, size);
	return (ptr);
}

char	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	if (!str1 || !str2)
		return (0);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (!(str1[i]) && !(str2[i]))
		return (1);
	return (0);
}

char	get_debug(int opt)
{
	if (opt == 1 && ft_strcmp(getenv("MALLOC_ALLOC_DEBUG"), "1"))
		return (1);
	if (opt == 2 && ft_strcmp(getenv("MALLOC_PRINT_DEBUG"), "1"))
		return (1);
	return (0);
}
