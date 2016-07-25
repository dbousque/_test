

#include "malloc.h"

void	*launch_option(t_malloc_data *data, char option, void *ptr,
														size_t size)
{
	if (option == ALLOC)
		return (my_malloc(data, size));
	else if (option == REALLOC)
		return (my_realloc(data, ptr, size));
	else if (option == FREE)
		my_free(data, ptr);
	else if (option == PRINT_MEM)
		print_mem(data);
	else if (option == DUMP_HEXA)
		malloc_dump_hexa(data);
	return (NULL);
}

void	*handle_malloc_option(size_t size, char option, void *ptr)
{
	static t_malloc_data	data = {{NULL, 0, 0}, {NULL, 0, 0},
									{NULL, 0, 0}, {NULL, 0, 0}, 0, 0, 0};

	if (!data.page_size)
	{
		data.page_size = getpagesize();
		data.zones.size = getpagesize() / sizeof(void*);
		data.zones.len = 0;
		data.zones.elts = (void**)my_mmap(sizeof(void*) * data.zones.size);
		if (!data.zones.elts)
		{
			data.page_size = 0;
			return (NULL);
		}
		data.free_small_blocks = ((t_linked_list){NULL, 0, 0});
		data.free_tiny_blocks = ((t_linked_list){NULL, 0, 0});
		data.raw_blocks = ((t_linked_list){NULL, 0, 0});
		data.debug_alloc = get_debug(1);
		data.debug_print = get_debug(2);
	}
	return (launch_option(&data, option, ptr, size));
}