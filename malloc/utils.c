/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:53:43 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 15:53:45 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	get_next_pagesize(size_t size)
{
	size_t	page_size;

	page_size = getpagesize();
	if (size % page_size == 0)
		return (size);
	return (size - (size % page_size) + page_size);
}

void	mmap_failed(void)
{
	char	*str;

	str = "allocation failed\n";
	write(2, str, ft_strlen(str));
}

void	munmap_failed(void)
{
	char	*str;

	str = "deallocation failed\n";
	write(2, str, ft_strlen(str));
}

void	*my_mmap(size_t size)
{
	void	*res;

	size = get_next_pagesize(size);
	res = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
			-1, 0);
	if (res == (void*)-1 || res == MAP_FAILED)
	{
		mmap_failed();
		return (NULL);
	}
	return (res);
}

void	my_munmap(void *ptr, size_t size)
{
	if (munmap(ptr, size) == -1)
		munmap_failed();
}
