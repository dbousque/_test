

#include "malloc.h"

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

void	malloc_dump(void)
{
	handle_malloc_option(0, DUMP_HEXA, NULL);
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

int		main(void)
{
	//int		i;
	//int		x;
	//char	*addr;
	//char	*list[1024];

	/*i = 0;
	while (i < 1024000)
	{
		addr = (char*)malloc(1024);
		list[i] = addr;
		x = 0;
		while (x < 1024)
		{
			addr[x] = 42;
			x++;
		}
		//free(addr);
		i++;
	}
	show_alloc_mem();*/
	char *lol = malloc(33);
	lol[2] = 42;
	lol = malloc(4201);
	lol[3] = 42;
	malloc_dump();
	return (0);
}

/*int		main(void)
{
	int		i;
	char 	*addr;
	size_t	size;
	i = 0;
	size = 0;
	addr = malloc(size);
	while (i < 10240)
	{*/
		//show_alloc_mem();
		//printf("BEFORE REALLOC : %zu\n", size);
		//fflush(stdout);
		//if (size > 4100)
		//	exit(1);
		//addr = malloc(size);
		//if (size % 100 == 0)
		//	free(addr);
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
/*		i++;
		size += 20;
	}
	show_alloc_mem();
	//assert42(addr, size - 20);
	return (0);
}*/





