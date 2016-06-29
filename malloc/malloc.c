

#include "malloc.h"



 #     include <stdlib.h>

#   include <stdio.h>

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

void	add_new_free_small_block(t_malloc_data *data, void *start, size_t size)
{
	t_small_block	*block;

	block = (t_small_block*)start;
	block->size = (uint32_t)size;
	block->free = 1;
	add_to_list(data->free_small_blocks, block);
}

int		add_new_small_zone(t_malloc_data *data)
{
	t_zone	*new_zone;
	size_t	alloc_size;

	alloc_size = get_small_zone_size(data);
	new_zone = (t_zone*)my_mmap(alloc_size);
	if (!new_zone)
		return (0);
	new_zone->type = SMALL;
	add_to_list(data->zones, new_zone);
	add_new_free_small_block(data, (void*)new_zone + sizeof(t_zone),
		alloc_size - sizeof(t_zone) - sizeof(t_small_block));
	return (1);
}

void	add_new_free_tiny_block(t_malloc_data *data, void *start, size_t size)
{
	t_tiny_block	*block;

	block = (t_tiny_block*)start;
	block->size = (uint16_t)size;
	block->free = 1;
	add_to_list(data->free_tiny_blocks, block);
}

int		add_new_tiny_zone(t_malloc_data *data)
{
	t_zone	*new_zone;
	size_t	alloc_size;

	alloc_size = get_tiny_zone_size(data);
	new_zone = (t_zone*)my_mmap(alloc_size);
	if (!new_zone)
		return (0);
	new_zone->type = TINY;
	add_to_list(data->zones, new_zone);
	add_new_free_tiny_block(data, (void*)new_zone + sizeof(t_zone),
		alloc_size - sizeof(t_zone) - sizeof(t_tiny_block));
	return (1);
}

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

void	print_tiny_block(t_tiny_block *block)
{
	char	*tmp_str;

	tmp_str = "  - tiny block of size ";
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

void	print_free_small_blocks(t_linked_list *free_small_blocks)
{
	size_t	i;
	char	*tmp_str;

	tmp_str = "Printing free blocks :\n";
	write(1, tmp_str, ft_strlen(tmp_str));
	i = 0;
	while (i < free_small_blocks->len)
	{
		print_number(i + 1);
		write(1, " :\n", 3);
		print_small_block(free_small_blocks->elts[i]);
		i++;
	}
}

t_malloc_data	*build_void_data(void)
{
	t_malloc_data	*data;

	data = my_mmap(sizeof(t_malloc_data));
	data->page_size = getpagesize();
	data->zones = new_linked_list();
	if (!data->zones)
		return (NULL);
	data->free_small_blocks = NULL;
	data->free_tiny_blocks = NULL;
	data->raw_blocks = NULL;
	/*data->free_small_blocks = new_linked_list();
	if (!data->free_small_blocks)
		return (NULL);
	if (!add_new_small_zone(data))
		return (NULL);
	data->free_tiny_blocks = new_linked_list();
	if (!data->free_tiny_blocks)
		return (NULL);
	if (!add_new_tiny_zone(data))
		return (NULL);
	data->raw_blocks = new_linked_list();
	if (!data->raw_blocks)
		return (NULL);*/
	return (data);
}

size_t	select_free_small_block(t_malloc_data *data, size_t size, int *error)
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
	if (!add_new_small_zone(data))
		*error = 1;
	return (data->free_small_blocks->len - 1);
}

size_t	select_free_tiny_block(t_malloc_data *data, size_t size, int *error)
{
	size_t			i;

	if (data->free_tiny_blocks->len > 0)
	{
		i = data->free_tiny_blocks->len - 1;
		while (1)
		{
			if (((t_tiny_block*)data->free_tiny_blocks->elts[i])->size >= size + sizeof(t_tiny_block))
				return (i);
			if (i == 0)
				break ;
			i--;
		}
	}
	if (!add_new_tiny_zone(data))
		*error = 1;
	return (data->free_tiny_blocks->len - 1);
}

void	remove_free_small_block(t_malloc_data *data, size_t ind)
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

void	remove_free_tiny_block(t_malloc_data *data, size_t ind)
{
	size_t	i;

	i = ind + 1;
	while (i < data->free_tiny_blocks->len)
	{
		data->free_tiny_blocks->elts[i - 1] = data->free_tiny_blocks->elts[i];
		i++;
	}
	data->free_tiny_blocks->len--;
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
		data->free_small_blocks->elts[ind] = new_free_block;
	else
		remove_free_small_block(data, ind);
	return ((void*)block + sizeof(t_small_block));
}

t_tiny_block	*alloc_tiny_block_for_use(t_malloc_data *data, size_t size,
																	size_t ind)
{
	t_tiny_block	*block;
	t_tiny_block	*new_free_block;
	char			new_free;

	new_free = 0;
	block = ((t_tiny_block*)data->free_tiny_blocks->elts[ind]);
	if (block->size > size + (sizeof(t_tiny_block) * 2))
	{
		new_free_block = (void*)block + size + sizeof(t_tiny_block);
		new_free_block->size = block->size - size - sizeof(t_tiny_block);
		new_free_block->free = 1;
		new_free = 1;
	}
	block->size = size;
	block->free = 0;
	if (new_free)
		data->free_tiny_blocks->elts[ind] = new_free_block;
	else
		remove_free_tiny_block(data, ind);
	return ((void*)block + sizeof(t_tiny_block));
}

size_t	get_next_pagesize(size_t size)
{
	size_t	page_size;

	page_size = getpagesize();
	if (size % page_size == 0)
		return (size);
	return (size - (size % page_size) + page_size);
}

void	*get_raw_block(t_malloc_data *data, size_t size)
{
	size_t	block_size;
	void	*ptr;
	size_t	*ptr_t;

	size += (sizeof(size_t) * 2);
	block_size = get_next_pagesize(size);
	ptr = my_mmap(block_size);
	if (!ptr)
		return (NULL);
	ptr_t = (size_t*)ptr;
	*ptr_t = block_size;
	ptr_t = (size_t*)(ptr + sizeof(size_t));
	*ptr_t = size - (sizeof(size_t) * 2);
	add_to_list(data->raw_blocks, ptr);
	return (ptr + (sizeof(size_t) * 2));
}

void	*alloc_tiny(t_malloc_data *data, size_t size)
{
	size_t			selected_ind;
	int				error;

	error = 0;
	if (!data->free_tiny_blocks)
	{
		data->free_tiny_blocks = new_linked_list();
		if (!data->free_tiny_blocks)
			return (NULL);
		if (!add_new_tiny_zone(data))
			return (NULL);
	}
	selected_ind = select_free_tiny_block(data, size, &error);
	if (error)
		return (NULL);
	return (alloc_tiny_block_for_use(data, size, selected_ind));
}

void	*alloc_small(t_malloc_data *data, size_t size)
{
	size_t			selected_ind;
	int				error;

	error = 0;
	if (!data->free_small_blocks)
	{
		data->free_small_blocks = new_linked_list();
		if (!data->free_small_blocks)
			return (NULL);
		if (!add_new_small_zone(data))
			return (NULL);
	}
	selected_ind = select_free_small_block(data, size, &error);
	if (error)
		return (NULL);
	return (alloc_small_block_for_use(data, size, selected_ind));
}

void	*alloc_new_block(t_malloc_data *data, size_t size)
{
	void			*block;

	if (size <= MAX_TINY_BLOCK)
		block = alloc_tiny(data, size);
	else if (size <= MAX_SMALL_BLOCK)
		block = alloc_small(data, size);
	else
	{
		if (!data->raw_blocks)
		{
			data->raw_blocks = new_linked_list();
			if (!data->raw_blocks)
				return (NULL);
		}
		block = get_raw_block(data, size);
	}
	return (block);
}

void	*my_malloc(t_malloc_data *data, size_t size)
{
	void	*ptr;

	ptr = alloc_new_block(data, size);
	return (ptr);
}

char	is_allocated_small_adress(t_malloc_data *data, void *ptr, t_small_block *start,
										void **prev_block, void **next_block)
{
	void	*block;
	void	*end;

	block = (void*)start;
	end = block + (get_small_zone_size(data) - sizeof(t_zone));
	while (block < end)
	{
		*next_block = block + ((size_t)((t_small_block*)block)->size + sizeof(t_small_block));
		if (*next_block >= end)
			*next_block = NULL;
		if (ptr == (block + sizeof(t_small_block)))
			return (1);
		*prev_block = block;
		block = *next_block;
	}
	return (0);
}

char	is_allocated_tiny_adress(t_malloc_data *data, void *ptr, t_tiny_block *start,
										void **prev_block, void **next_block)
{
	void	*block;
	void	*end;

	block = (void*)start;
	end = block + (get_tiny_zone_size(data) - sizeof(t_zone));
	while (block < end)
	{
		*next_block = block + ((size_t)((t_tiny_block*)block)->size + sizeof(t_tiny_block));
		if (*next_block >= end)
			*next_block = NULL;
		if (ptr == (block + sizeof(t_tiny_block)))
			return (1);
		*prev_block = block;
		block = *next_block;
	}
	return (0);
}

size_t	is_raw_block(t_malloc_data *data, void *ptr)
{
	size_t	i;

	if (!data->raw_blocks)
		return (0);
	i = data->raw_blocks->len - 1;
	while (1)
	{
		if ((data->raw_blocks->elts[i] + (sizeof(size_t) * 2)) == ptr)
			return (i + 1);
		if (i == 0)
			break ;
		i--;
	}
	return (0);
}

size_t	get_zone_type(t_malloc_data *data, void *ptr, void **prev_block, void **next_block)
{
	size_t	i;
	size_t	tiny_zone_size;
	size_t	small_zone_size;
	void	*start;

	tiny_zone_size = get_tiny_zone_size(data);
	small_zone_size = get_small_zone_size(data);
	i = data->zones->len - 1;
	while (1)
	{
		start = (void*)(data->zones->elts[i]);
		if (ptr > start)
		{
			if (((t_zone*)start)->type == SMALL && ptr < start + small_zone_size)
				return (is_allocated_small_adress(data, ptr, start + sizeof(t_zone), prev_block, next_block) ? SMALL : 0);
			if (((t_zone*)start)->type == TINY && ptr < start + tiny_zone_size)
				return (is_allocated_tiny_adress(data, ptr, start + sizeof(t_zone), prev_block, next_block) ? TINY : 0);
		}
		if (i == 0)
			break ;
		i--;
	}
	return (is_raw_block(data, ptr) + 3);
}

void	change_free_tiny(t_malloc_data *data, void *from, void *to)
{
	size_t	i;

	i = data->free_tiny_blocks->len - 1;
	while (1)
	{
		if (data->free_tiny_blocks->elts[i] == from)
		{
			data->free_tiny_blocks->elts[i] = to;
			return ;
		}
		if (i == 0)
			break ;
		i--;
	}
	write(1, "COULD NOT CHANGE TINY\n", ft_strlen("COULD NOT CHANGE TINY\n"));
} 

void	change_free_small(t_malloc_data *data, void *from, void *to)
{
	size_t	i;

	i = data->free_small_blocks->len - 1;
	while (1)
	{
		if (data->free_small_blocks->elts[i] == from)
		{
			data->free_small_blocks->elts[i] = to;
			return ;
		}
		if (i == 0)
			break ;
		i--;
	}
	write(1, "COULD NOT CHANGE SMAL\n", ft_strlen("COULD NOT CHANGE SMAL\n"));
}

void	free_tiny(t_malloc_data *data, void *ptr, void *prev_block, void *next_block)
{
	char	next_block_free;
	char	prev_block_free;

	next_block_free = next_block && ((t_tiny_block*)next_block)->free == 1;
	prev_block_free = prev_block && ((t_tiny_block*)prev_block)->free == 1;
	if (((t_tiny_block*)ptr)->free == 1)
		return ;
	((t_tiny_block*)ptr)->free = 1;
	if (prev_block_free)
	{
		if (next_block_free)
		{
			((t_tiny_block*)prev_block)->size += (sizeof(t_tiny_block) * 2)
					+ ((t_tiny_block*)next_block)->size + ((t_tiny_block*)ptr)->size;
		}
		else
			((t_tiny_block*)prev_block)->size += sizeof(t_tiny_block) + ((t_tiny_block*)ptr)->size;
	}
	else if (next_block_free)
	{
		((t_tiny_block*)ptr)->size += sizeof(t_tiny_block) + ((t_tiny_block*)next_block)->size;
		change_free_tiny(data, next_block, ptr);
	}
	else
		add_to_list(data->free_tiny_blocks, ptr);
}

void	free_small(t_malloc_data *data, void *ptr, void *prev_block, void *next_block)
{
	char	next_block_free;
	char	prev_block_free;

	next_block_free = next_block && ((t_small_block*)next_block)->free == 1;
	prev_block_free = prev_block && ((t_small_block*)prev_block)->free == 1;
	if (((t_small_block*)ptr)->free == 1)
		return ;
	((t_small_block*)ptr)->free = 1;
	if (prev_block_free)
	{
		if (next_block_free)
		{
			((t_small_block*)prev_block)->size += (sizeof(t_small_block) * 2)
					+ ((t_small_block*)next_block)->size + ((t_small_block*)ptr)->size;
		}
		else
			((t_small_block*)prev_block)->size += sizeof(t_small_block) + ((t_small_block*)ptr)->size;
	}
	else if (next_block_free)
	{
		((t_small_block*)ptr)->size += sizeof(t_small_block) + ((t_small_block*)next_block)->size;
		change_free_small(data, next_block, ptr);
	}
	else
		add_to_list(data->free_small_blocks, ptr);
}

void	free_raw_block(t_malloc_data *data, size_t ind)
{
	size_t	i;

	my_munmap(data->raw_blocks->elts[ind], *((size_t*)(data->raw_blocks->elts[ind])));
	data->raw_blocks->elts[ind] = NULL;
	i = ind + 1;
	while (i < data->raw_blocks->len)
	{
		data->raw_blocks->elts[i - 1] = data->raw_blocks->elts[i];
		i++;
	}
	data->raw_blocks->len--;
}

void	my_free(t_malloc_data *data, void *ptr)
{
	size_t	zone_type;
	void	*prev_block;
	void	*next_block;

	if (!ptr)
		return ;
	prev_block = NULL;
	next_block = NULL;
	zone_type = get_zone_type(data, ptr, &prev_block, &next_block);
	printf("zone type : %zu\n", zone_type);
	fflush(stdout);
	if (zone_type == 3 || zone_type == 0)
		return ;
	if (zone_type == TINY)
		free_tiny(data, (ptr - sizeof(t_tiny_block)), prev_block, next_block);
	else if (zone_type == SMALL)
		free_small(data, (ptr - sizeof(t_small_block)), prev_block, next_block);
	else
		free_raw_block(data, zone_type - 4);
}

void	print_zone_info(t_zone *zone)
{
	char	*tmp_str;

	tmp_str = "  - number of allocated blocks : ";
	write(1, tmp_str, ft_strlen(tmp_str));
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
		end = (void*)zone + get_small_zone_size(data);
	else if (zone->type == TINY)
		end = (void*)zone + get_tiny_zone_size(data);
	block = (void*)zone + sizeof(t_zone);
	while (block < end)
	{
		if (zone->type == SMALL)
			print_small_block(block);
		else if (zone->type == TINY)
			print_tiny_block(block);
		if (zone->type == SMALL)
			block += ((t_small_block*)block)->size + sizeof(t_small_block);
		else if (zone->type == TINY)
			block += ((t_tiny_block*)block)->size + sizeof(t_tiny_block);
		else
		{
			write(1, "UNIMPLEMENTED\n", 14);
		}
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

void	print_raw_blocks(t_malloc_data *data)
{
	size_t	i;
	char	*tmp_str;

	if (!data->raw_blocks)
		return ;
	tmp_str = "Printing large blocks : \n";
	write(1, tmp_str, ft_strlen(tmp_str));
	i = 0;
	while (i < data->raw_blocks->len)
	{
		print_number(i + 1);
		tmp_str = " : \n  - block of size ";
		write(1, tmp_str, ft_strlen(tmp_str));
		print_number(*((size_t*)(data->raw_blocks->elts[i] + sizeof(size_t))));
		write(1, "\n", 1);
		i++;
	}
}

void	print_mem(t_malloc_data *data)
{
	//print_free_small_blocks(data->free_small_blocks);
	print_zones(data);
	print_raw_blocks(data);
}

void	*handle_malloc_option(size_t size, char option, void *ptr)
{
	static t_malloc_data	*data = NULL;

	if (!data)
		data = build_void_data();
	if (!data)
		return (NULL);
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

void	free(void *ptr)
{
	handle_malloc_option(0, FREE, ptr);
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

int		main(void)
{
	int		i;
	int		x;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		x = 0;
		while (x < 1024)
		{
			addr[x] = 42;
			x++;
		}
		i++;
	}
	show_alloc_mem();
	return (0);
}