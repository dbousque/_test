

#include "malloc.h"


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	mmap_failed(void)
{
	char	*str;

	str = "allocation failed\n";
	write(2, str, ft_strlen(str));
	exit(1);
}

void	munmap_failed(void)
{
	char	*str;

	str = "deallocation failed\n";
	write(2, str, ft_strlen(str));
	fflush(stdout);
	printf("%s\n", strerror(errno));
	exit(1);
}

void	*my_mmap(size_t size)
{
	void	*res;

	res = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
			-1, 0);
	if (res == (void*)-1 || res == MAP_FAILED)
		mmap_failed();
	return (res);
}

void	my_munmap(void *ptr, size_t size)
{
	if (munmap(ptr, size) == -1)
		munmap_failed();
}

void	add_new_free_small_block(t_malloc_data *data, void *start, size_t size)
{
	t_small_block	*block;

	block = (t_small_block*)start;
	block->size = (uint16_t)size;
	block->free = 1;
	add_to_list(data->free_small_blocks, block);
}

void	add_new_small_zone(t_malloc_data *data)
{
	t_zone	*new_zone;

	//printf("len : %ld,  size : %ld\n", data->zones->len, data->zones->size);
	//fflush(stdout);
	new_zone = (t_zone*)my_mmap(NB_PAGES_PER_SMALL_ZONE * data->page_size);
	new_zone->nb_used_blocks = 0;
	new_zone->type = SMALL;
	add_to_list(data->zones, new_zone);
	add_new_free_small_block(data, (void*)new_zone + sizeof(t_zone),
		NB_PAGES_PER_SMALL_ZONE * data->page_size
		- sizeof(t_zone) - sizeof(t_small_block));
}

/*void	add_new_tiny_zone(t_malloc_data *data)
{
	t_zone	*new_zone;

	new_zone = (t_zone*)my_mmap(NB_PAGES_PER_TINY_ZONE * data->page_size);
	new_zone->nb_used_blocks = 0;
	new_zone->type = TINY;
	add_to_list(data->zones, new_zone);
}*/

void	print_small_block(t_small_block *block)
{
	char	*tmp_str;

	tmp_str = "  - small block of size ";
	write(1, tmp_str, ft_strlen(tmp_str));
	print_number(block->size);
	write(1, "\n", 1);
	tmp_str = "  - free : ";
	write(1, tmp_str, ft_strlen(tmp_str));
	if (block->free)
		tmp_str = "Yes\n";
	else
		tmp_str = "No\n";
	write(1, tmp_str, ft_strlen(tmp_str));
}

void	print_free_blocks(t_linked_list *free_blocks)
{
	size_t	i;
	char	*tmp_str;

	tmp_str = "Printing free blocks :\n";
	write(1, tmp_str, ft_strlen(tmp_str));
	i = 0;
	while (i < free_blocks->len)
	{
		print_number(i + 1);
		write(1, " :\n", 3);
		print_small_block(free_blocks->elts[i]);
		i++;
	}
}

t_malloc_data	*build_void_data(void)
{
	t_malloc_data	*data;

	data = my_mmap(sizeof(t_malloc_data));
	data->page_size = getpagesize();
	data->zones = new_linked_list();
	data->free_small_blocks = new_linked_list();
	add_new_small_zone(data);
	print_free_blocks(data->free_small_blocks);
	//add_new_tiny_zone(data);
	return (data);
}

size_t	select_free_block(t_malloc_data *data, size_t size)
{
	size_t			i;

	if (data->free_small_blocks->len > 0)
	{
		i = data->free_small_blocks->len - 1;
		while (1)
		{
			if (((t_small_block*)data->free_small_blocks->elts[i])->size >= size + sizeof(t_small_block))
				return (i);
			if (i == 0)
				break ;
			i--;
		}
	}
	//printf("ADDING SMALL BLOCK\n");
	//fflush(stdout);
	add_new_small_zone(data);
	//printf("ADDED BLOCK\n");
	//fflush(stdout);
	return (data->free_small_blocks->len - 1);
}

void	remove_free_block(t_malloc_data *data, size_t ind)
{
	size_t	i;

	i = ind + 1;
	while (i < data->free_small_blocks->len)
	{
		data->free_small_blocks->elts[i - 1] = data->free_small_blocks->elts[i];
		i++;
	}
	data->free_small_blocks->len--;
}

t_small_block	*alloc_small_block_for_use(t_malloc_data *data, size_t size,
																	size_t ind)
{
	t_small_block	*block;
	t_small_block	*new_free_block;
	char			new_free;

	new_free = 0;
	block = ((t_small_block*)data->free_small_blocks->elts[ind]);
	if (block->size > size + (sizeof(t_small_block) * 2))
	{
		new_free_block = (void*)block + size + sizeof(t_small_block);
		new_free_block->size = block->size - size - sizeof(t_small_block);
		new_free_block->free = 1;
		new_free = 1;
	}
	block->size = size;
	block->free = 0;
	if (new_free)
	{
		data->free_small_blocks->elts[ind] = new_free_block;
	}
	else
	{
		remove_free_block(data, ind);
		char 	*str = (char*)block + sizeof(t_small_block);
		int x = 0;
		while (x < 10)
		{
			str[x] = 'A';
			x++;
		}
	}
	return ((void*)block + sizeof(t_small_block));
}

void	*alloc_new_small_block(t_malloc_data *data, size_t size)
{
	size_t			selected_ind;
	t_small_block	*block;

	selected_ind = select_free_block(data, size);
	block = alloc_small_block_for_use(data, size, selected_ind);
	return (block);
}

void	*my_malloc(t_malloc_data *data, size_t size)
{
	void	*ptr;

	ptr = alloc_new_small_block(data, size);
	return (ptr);
}

void	my_free(t_malloc_data *data, void *ptr)
{
	(void)data;
	(void)ptr;
}

void	print_zone_info(t_zone *zone)
{
	char	*tmp_str;

	tmp_str = "  - number of allocated blocks : ";
	write(1, tmp_str, ft_strlen(tmp_str));
	print_number(zone->nb_used_blocks);
	write(1, "\n", 1);
	tmp_str = "  - type of zone : ";
	write(1, tmp_str, ft_strlen(tmp_str));
	if (zone->type == TINY)
		tmp_str = "TINY";
	else if (zone->type == SMALL)
		tmp_str = "SMALL";
	else if (zone->type == LARGE)
		tmp_str = "LARGE";
	else
		tmp_str = "UNKNOWN TYPE!";
	write(1, tmp_str, ft_strlen(tmp_str));
	write(1, "\n", 1);
}

void	print_zone_content(t_malloc_data *data, t_zone *zone)
{
	void	*block;
	void	*end;

	end = NULL;
	if (zone->type == SMALL)
		end = (void*)zone + (NB_PAGES_PER_SMALL_ZONE * data->page_size);
	block = (void*)zone + sizeof(t_zone);
	while (block < end)
	{
		print_small_block(block);
		block += ((t_small_block*)block)->size + sizeof(t_small_block);
	}
}

void	print_zone(t_malloc_data *data, t_zone *zone)
{
	print_zone_info(zone);
	print_zone_content(data, zone);
}

void	print_zones(t_malloc_data *data)
{
	size_t	i;
	char	*tmp_str;

	tmp_str = "Printing zones : \n";
	write(1, tmp_str, ft_strlen(tmp_str));
	i = 0;
	while (i < data->zones->len)
	{
		print_number(i + 1);
		write(1, " :\n", 3);
		print_zone(data, data->zones->elts[i]);
		i++;
	}
}

void	print_mem(t_malloc_data *data)
{
	print_free_blocks(data->free_small_blocks);
	//print_zones(data);
}

void	*handle_malloc_option(size_t size, char option, void *ptr)
{
	static t_malloc_data	*data = NULL;

	if (!data)
		data = build_void_data();
	if (option == ALLOC)
		return (my_malloc(data, size));
	else if (option == FREE)
		my_free(data, ptr);
	else if (option == PRINT_MEM)
		print_mem(data);
	return (NULL);
}

void	*malloc(size_t size)
{
	return (handle_malloc_option(size, ALLOC, NULL));
}

void	show_alloc_mem_ex(void)
{
	handle_malloc_option(0, PRINT_MEM, NULL);
}

/*int		main(void)
{
	char	*str;
	int		i;
	int		x;

	i = 0;
	while (i < 10000000)
	{
		//print_number(i);
		//write(1, "\n", 1);
		//if (i >= 37829)
		//{
		//	printf("   BEFORE\n");
		//	fflush(stdout);
		//	show_alloc_mem_ex();
		//}
		//printf("BEFORE MALLOC\n");
		//fflush(stdout);
		str = (char*)malloc(sizeof(char) * 10);
		(void)str;
		//if (i >= 37829)
		//{
		//	printf("   AFTER\n");
		//	fflush(stdout);
		//	show_alloc_mem_ex();
		//}
		//printf("AFTER MALLOC\n");
		//fflush(stdout);
		x = 0;
		while (x < 10)
		{
			str[x] = 'A';
			x++;
		}
		//printf("AFTER WHILE\n");
		//fflush(stdout);
		//free(str);
		i++;
	}
	printf("END OF PROGRAMM\n");
	fflush(stdout);
	//printf("size of t_zone : %ld\nsize of small_block : %ld\n", sizeof(t_zone), sizeof(t_small_block));
	//show_alloc_mem_ex();
	return (0);
}*/

int		main(void)
{
	int		i;
	char	*addr;

	//return (0);
	i = 0;
	while (i < 102400)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		i++;
	}
	return (0);
}