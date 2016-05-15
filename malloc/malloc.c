

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

void	init_small_block(void *location, size_t size)
{
	t_small_block	*block;

	block = (t_small_block*)location;
	block->size = (uint16_t)size;
	block->free = 1;
}

void	add_new_small_zone(t_malloc_data *data)
{
	t_zone	*new_zone;

	new_zone = (t_zone*)my_mmap(NB_PAGES_PER_SMALL_ZONE * data->page_size);
	new_zone->nb_used_blocks = 0;
	new_zone->type = SMALL;
	init_small_block(new_zone + sizeof(t_zone),
					NB_PAGES_PER_TINY_ZONE * data->page_size - sizeof(t_zone));
	add_to_list(data->zones, new_zone);
}

void	add_new_tiny_zone(t_malloc_data *data)
{
	t_zone	*new_zone;

	new_zone = (t_zone*)my_mmap(NB_PAGES_PER_TINY_ZONE * data->page_size);
	new_zone->nb_used_blocks = 0;
	new_zone->type = TINY;
	add_to_list(data->zones, new_zone);
}

t_malloc_data	*build_void_data(void)
{
	t_malloc_data	*data;

	data = my_mmap(sizeof(t_malloc_data));
	data->page_size = getpagesize();
	data->zones = new_linked_list();
	add_new_small_zone(data);
	add_new_tiny_zone(data);
	return (data);
}

void	*my_malloc(size_t size)
{
	static t_malloc_data	*data = NULL;

	if (!data)
		data = build_void_data();
	//print_zones(data->zones);
	return (my_mmap(size));
}

void	*handle_malloc_option(size_t size, char option)
{
	if (option == ALLOC)
		return (my_malloc(size));
	return (NULL);
}

void	*malloc(size_t size)
{
	return (handle_malloc_option(size, ALLOC));
}

int		main(void)
{
	char	*str;
	int		i;
	int		x;

	i = 0;
	while (i < 100)
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