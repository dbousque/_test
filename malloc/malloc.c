

#include "malloc.h"

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
	data->free_small_blocks = new_linked_list();
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
		return (NULL);
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
	return (size / page_size + page_size);
}

void	*get_raw_block(t_malloc_data *data, size_t size)
{
	size_t	block_size;
	void	*ptr;

	block_size = get_next_pagesize(size);
	ptr = my_mmap(block_size);
	if (!ptr)
		return (NULL);
	add_to_list(data->raw_blocks, ptr);
	return (ptr);
}

void	*alloc_new_block(t_malloc_data *data, size_t size)
{
	size_t			selected_ind;
	void			*block;
	int				error;

	error = 0;
	if (size <= MAX_TINY_BLOCK)
	{
		selected_ind = select_free_tiny_block(data, size, &error);
		if (error)
			return (NULL);
		block = alloc_tiny_block_for_use(data, size, selected_ind);
	}
	else if (size <= MAX_SMALL_BLOCK)
	{
		selected_ind = select_free_small_block(data, size, &error);
		if (error)
			return (NULL);
		block = alloc_small_block_for_use(data, size, selected_ind);
	}
	else
		block = get_raw_block(data, size);
	return (block);
}

void	*my_malloc(t_malloc_data *data, size_t size)
{
	void	*ptr;

	ptr = alloc_new_block(data, size);
	return (ptr);
}

char	is_allocated_small_adress(t_malloc_data *data, void *ptr, t_small_block *start)
{
	void	*block;

	block = (void*)start;
	while (1)
	{
		
		block += ((t_small_block*)block)->size + sizeof(t_small_block);
	}
}

char	get_zone_type(t_malloc_data *data, void *ptr)
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
		start = (void*)*(data->zones->elts[i]);
		if (ptr > start)
		{
			if (((t_zone*)start)->type == SMALL && ptr < start + small_zone_size)
				return (is_allocated_small_adress(data, ptr, start + sizeof(t_zone)) ? 2 : -1);
			if (((t_zone*)start)->type == TINY && ptr < start + tiny_zone_size)
				return (is_allocated_tiny_adress(data, ptr, start + sizeof(t_zone)) ? 2 : -1);
		}
		if (i == 0)
			break ;
		i--;
	}
	return (is_raw_block(data, ptr) ? 3 : -1);
}

#include <stdio.h>
void	my_free(t_malloc_data *data, void *ptr)
{
	char	zone_type;

	zone_type = get_zone_type(data, ptr);
	printf("zone type : %d\n", zone_type);
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

void	print_mem(t_malloc_data *data)
{
	print_free_small_blocks(data->free_small_blocks);
	print_zones(data);
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

void	show_alloc_mem(void)
{
	handle_malloc_option(0, PRINT_MEM, NULL);
}

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