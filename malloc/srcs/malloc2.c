/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:52:03 by dbousque          #+#    #+#             */
/*   Updated: 2016/08/15 12:45:48 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*launch_option2(t_malloc_data *data, char option, void *ptr,
															size_t size)
{
	void	*res;
	void	*to_ret;
	char	mock;

	res = NULL;
	if (option == DUMP_HEXA)
		malloc_dump_hexa(data);
	else if (option == ALLOC)
		res = my_malloc(data, size);
	else if (option == REALLOC)
		res = my_realloc(data, ptr, size, &mock);
	else if (option == REALLOCF)
		res = my_reallocf(data, ptr, size);
	else if (option == FREE)
		my_free(data, ptr);
	else if (option == HELP)
		malloc_help2();
	to_ret = res;
	if (data->print_calls)
		print_malloc_return(option, res);
	pthread_mutex_unlock(&g_lock);
	return (to_ret);
}

void	*launch_option(t_malloc_data *data, char option, void *ptr,
															size_t size)
{
	if (data->print_calls)
		print_malloc_call(option, ptr, size);
	if (option == PRINT_MEM || data->show_at_each_turn >= 2)
		print_mem(data);
	if (option == DUMP_FREE || data->show_at_each_turn % 2 == 1)
		malloc_dump_free(data);
	return (launch_option2(data, option, ptr, size));
}

void	get_debugs(t_malloc_data *data)
{
	data->debug_alloc = get_debug(1);
	data->debug_print = get_debug(2);
	data->print_calls = get_debug(3);
	data->show_at_each_turn = get_debug(4) * 16;
	data->show_at_each_turn += get_debug(5);
}

void	*handle_malloc_option(size_t size, char option, void *ptr)
{
	static t_md	d = {{N, 0, 0}, {N, 0, 0}, {N, 0, 0}, {N, 0, 0}, 0, 0, 0, 0, 0};

	if (!d.page_size)
		pthread_mutex_init(&g_lock, NULL);
	pthread_mutex_lock(&g_lock);
	if (!d.page_size)
	{
		d.page_size = getpagesize();
		d.zones.size = getpagesize() / sizeof(void*);
		d.zones.len = 0;
		d.zones.elts = (void**)my_mmap(sizeof(void*) * d.zones.size);
		if (!d.zones.elts)
		{
			d.page_size = 0;
			pthread_mutex_unlock(&g_lock);
			return (NULL);
		}
		d.free_small_blocks = ((t_linked_list){NULL, 0, 0});
		d.free_tiny_blocks = ((t_linked_list){NULL, 0, 0});
		d.raw_blocks = ((t_linked_list){NULL, 0, 0});
		get_debugs(&d);
	}
	return (launch_option(&d, option, ptr, size));
}

void	malloc_free_zones(void)
{
	handle_malloc_option(0, DUMP_FREE, NULL);
}
