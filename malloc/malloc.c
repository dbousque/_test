

#include "malloc.h"



#   include <stdio.h>

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

void	*malloc(size_t size)
{
	return (handle_malloc_option(size, ALLOC, NULL));
}

void	free(void *ptr)
{
	handle_malloc_option(0, FREE, ptr);
}

void	*realloc(void *ptr, size_t size)
{
	return (handle_malloc_option(size, REALLOC, ptr));
}

void	show_alloc_mem(void)
{
	handle_malloc_option(0, PRINT_MEM, NULL);
}

/*int		main(void)
{
	void	*ptr;
	void	*ptr2;
	void	*ptr3;

	show_alloc_mem();
	(void)ptr3;
	ptr = malloc(8192);
	ptr2 = malloc(1);
	free(ptr2);
	ptr2 = malloc(1);
	ptr3 = malloc(56798);
	show_alloc_mem();
	free(ptr);
	free(ptr2);
	show_alloc_mem();
	free(ptr3);
	return (0);
}*/

/*int		main(void)
{
	int		i;
	int		x;
	char	*addr;
	char	*list[1024];

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		list[i] = addr;
		x = 0;
		while (x < 1024)
		{
			addr[x] = 42;
			x++;
		}
		if (i == 512)
		{
			i = 0;
			while (i <= 512)
			{
				free(list[i]);
				//free(list[i]);
				i++;
			}
			i = 512;
		}
		//free(addr);
		i++;
	}
	show_alloc_mem();
	return (0);
}*/

void	assert42(char *addr, size_t size)
{
	int		i;

	i = 0;
	while (i < (int)size)
	{
		if (addr[i] != 42)
		{
			printf("NOT ALL 42!!!\n");
			fflush(stdout);
			return ;
		}
		i++;
	}
	printf("ALLL 42!!!\n");
	fflush(stdout);
}


#  include <stdlib.h>

int		main(void)
{
	int		i;
	char 	*addr;
	size_t	size;
	//int		x;
	//char	*lol;

	//*lol = 2;
	//free(lol);
	i = 0;
	size = 0;
	addr = malloc(size);
	while (i < 10240)
	{
		//show_alloc_mem();
		//printf("BEFORE REALLOC : %zu\n", size);
		//fflush(stdout);
		//if (size > 4100)
		//	exit(1);
		addr = realloc(addr, size);
		//free(addr);
		//printf("AFTER REALLOC\n");
		//fflush(stdout);
		/*x = size - 20;
		while (x >= 0 && x < (int)size)
		{
			addr[x] = 42;
			x++;
		}*/
		//printf("BEFORE FREE\n");
		//fflush(stdout);
		/*if (addr)
			free(addr);
		free(addr);
		free(addr);
		free(addr + 1);
		free(addr + 10);
		free(addr + 10 + sizeof(t_small_block));
		free(NULL);*/
		i++;
		size += 20;
	}
	show_alloc_mem();
	//assert42(addr, size - 20);
	return (0);
}





