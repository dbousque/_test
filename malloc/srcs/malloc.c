/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:51:57 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 15:51:59 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	void	*res;

	write(1, "MALLOC CALLED\n", 14);
	res = handle_malloc_option(size, ALLOC, NULL);
	write(1, "MALLOC END   \n", 14);
	return (res);
}

void	free(void *ptr)
{
	write(1, "FREE CALLED\n", 12);
	handle_malloc_option(0, FREE, ptr);
	write(1, "FREE END   \n", 12);
}

void	*realloc(void *ptr, size_t size)
{
	void	*res;

	write(1, "REALLOC CALLED\n", 15);
	res = handle_malloc_option(size, REALLOC, ptr);
	write(1, "REALLOC END   \n", 15);
	return (res);
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



//#   include <stdio.h>

//int		main(void)
//{
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
	/*char *lol = malloc(33);
	(void)lol;
	lol[2] = 42;
	char *lol2 = malloc(25);
	char *lol3 = malloc(56);
	(void)lol3;
	free(lol2);
	lol = malloc(3455);
	lol[3] = 42;
	show_alloc_mem();
	malloc_dump();
	malloc_free_zones();
	return (0);
}*/

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





