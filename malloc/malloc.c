

#include "malloc.h"


#include <stdlib.h>
#include <stdio.h>


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
	exit(1);
}

void	*my_mmap(size_t size)
{
	void	*res;

	res = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
			-1, 0);
	if (res == (void*)-1)
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

	new_zone = (t_zone*)my_mmap(NB_PAGES_PER_SMALL_ZONE * data->page_size);
	new_zone->nb_used_blocks = 0;
	new_zone->type = SMALL;
	add_to_list(data->zones, new_zone);
	add_new_free_small_block(data, new_zone + sizeof(t_zone),
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
		tmp_str = "Yes";
	else
		tmp_str = "No";
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

t_small_block	**select_small_block(t_malloc_data *data, size_t size)
{
	size_t			i;
	t_small_block	*tmp_block;

	i = 0;
	while (i < data->free_small_blocks->len)
	{
		tmp_block = (t_small_block*)data->free_small_blocks->elts[i];
		if (tmp_block->size >= size)
			return ((t_small_block**)&(data->free_small_blocks->elts[i]));
		i++;
	}
	add_new_small_zone(data);
	return ((t_small_block**)&(data->free_small_blocks->elts[data->free_small_blocks->len - 1]));
}

void	remove_free_block(t_malloc_data *data, t_small_block **free_block)
{
	size_t	i;
	size_t	x;

	char *tmp_str = "removing\n";
	write(1, tmp_str, ft_strlen(tmp_str));
	fflush(stdout);
	i = data->free_small_blocks->len - 1;
	while (1)
	{
		if (data->free_small_blocks->elts[i] == *free_block)
		{
			x = i + 1;
			while (x < data->free_small_blocks->len)
			{
				data->free_small_blocks->elts[x - 1] = data->free_small_blocks->elts[x];
				x++;
			}
			data->free_small_blocks->len--;
			return ;
		}
		if (i == 0)
			break ;
		i--;
	}
	tmp_str = "Error, free_block not found\n";
	write(1, tmp_str, ft_strlen(tmp_str));
}

void	reserve_small_block(t_malloc_data *data, t_small_block **free_block,
																size_t size)
{
	t_small_block	*new_free_block;
	char			replace_free_block;

	replace_free_block = 0;
	if ((*free_block)->size > size + sizeof(t_small_block))
	{
		new_free_block = (*free_block) + sizeof(t_small_block) + size;
		new_free_block->size = (*free_block)->size;
		new_free_block->free = 1;
		replace_free_block = 1;
	}
	(*free_block)->size = size;
	(*free_block)->free = 0;
	if (replace_free_block)
		*free_block = (*free_block) + sizeof(t_small_block) + size;
	else
	{
		char *tmp_str = "there\n";
		write(1, tmp_str, ft_strlen(tmp_str));
		fflush(stdout);
		remove_free_block(data, free_block);
	}
}

void	*alloc_new_small_block(t_malloc_data *data, size_t size)
{
	t_small_block	**selected_block;

	char *tmp_str = "before\n";
	write(1, tmp_str, ft_strlen(tmp_str));
	fflush(stdout);
	selected_block = select_small_block(data, size);
	tmp_str = "between\n";
	write(1, tmp_str, ft_strlen(tmp_str));
	fflush(stdout);
	reserve_small_block(data, selected_block, size);
	tmp_str = "after\n";
	write(1, tmp_str, ft_strlen(tmp_str));
	fflush(stdout);
	return (*selected_block + sizeof(t_small_block));
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

void	*handle_malloc_option(size_t size, char option, void *ptr)
{
	static t_malloc_data	*data = NULL;

	if (!data)
		data = build_void_data();
	if (option == ALLOC)
		return (my_malloc(data, size));
	else if (option == FREE)
		my_free(data, ptr);
	return (NULL);
}

void	*malloc(size_t size)
{
	return (handle_malloc_option(size, ALLOC, NULL));
}

int		main(void)
{
	char	*str;
	int		i;
	int		x;

	i = 0;
	while (i < 288)
	{
		str = malloc(sizeof(char) * 10);
		x = 0;
		while (x < 10)
		{
			str[x] = 'A';
			x++;
		}
		//free(str);
		i++;
	}
	//printf("size of t_zone : %ld\nsize of small_block : %ld\n", sizeof(t_zone), sizeof(t_small_block));
	return (0);
}

/*int		main(void)
{
	char	*ptr;
	int		i;

	ptr = malloc(32);
	i = 0;
	while (i < 9)
	{
		ptr[i] = 'A';
		i++;
	}
	ptr[i] = '\0';
	printf("%s   |   %p\n", ptr, ptr);
	i = -16;
	while (i <= 0)
	{
		printf("%02X  ", *(ptr + i));
		i++;
	}
	return (0);
}*/