/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:52:03 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 16:47:35 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"


  # include <stdio.h>

void	*launch_option(t_malloc_data *data, char option, void *ptr,
														size_t size, char mock)
{
	void	*res;
	void	*to_ret;

	if (data->print_calls)
		print_malloc_call(option, ptr, size);
	res = NULL;
	if (option == PRINT_MEM || data->show_alloc_at_each_turn)
		print_mem(data);
	if (option == DUMP_FREE || data->show_free_at_each_turn)
		malloc_dump_free(data);
	if (option == DUMP_HEXA)
		malloc_dump_hexa(data);
	else if (option == ALLOC)
		res = my_malloc(data, size);
	else if (option == REALLOC)
		res = my_realloc(data, ptr, size, &mock);
	else if (option == CALLOC)
		res = my_calloc(data, size);
	else if (option == REALLOCF)
		res = my_reallocf(data, ptr, size);
	else if (option == FREE)
		my_free(data, ptr);
	to_ret = res;
	if (data->print_calls)
		print_malloc_return(option, res);
	pthread_mutex_unlock(&lock);
	return (to_ret);
}

void	*handle_malloc_option(size_t size, char option, void *ptr)
{
	static t_md	data = {{N, 0, 0}, {N, 0, 0}, {N, 0, 0}, {N, 0, 0}, 0, 0, 0, 0, 0, 0};

	if (!data.page_size)
		pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	if (!data.page_size)
	{
		data.page_size = getpagesize();
		data.zones.size = getpagesize() / sizeof(void*);
		data.zones.len = 0;
		data.zones.elts = (void**)my_mmap(sizeof(void*) * data.zones.size);
		if (!data.zones.elts)
		{
			data.page_size = 0;
			pthread_mutex_unlock(&lock);
			return (NULL);
		}
		data.free_small_blocks = ((t_linked_list){NULL, 0, 0});
		data.free_tiny_blocks = ((t_linked_list){NULL, 0, 0});
		data.raw_blocks = ((t_linked_list){NULL, 0, 0});
		data.debug_alloc = get_debug(1);
		data.debug_print = get_debug(2);
		data.print_calls = get_debug(3);
		data.show_alloc_at_each_turn = get_debug(4);
		data.show_free_at_each_turn = get_debug(5);
	}
	return (launch_option(&data, option, ptr, size, 0));
}

void	malloc_free_zones(void)
{
	handle_malloc_option(0, DUMP_FREE, NULL);
}
