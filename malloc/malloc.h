

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdint.h>
# include <unistd.h>

# define ALLOC 1
# define FREE 2
# define PRINT_MEM 3
# define NB_PAGES_PER_SMALL_ZONE 128
# define NB_PAGES_PER_TINY_ZONE 16
# define MAX_SMALL_BLOCK 4000
# define MAX_TINY_BLOCK 255
# define TINY 1
# define SMALL 2
# define LARGE 3

typedef struct		s_linked_list
{
	void			**elts;
	size_t			size;
	size_t			len;
}					t_linked_list;

typedef struct		s_malloc_data
{
	t_linked_list	*zones;
	t_linked_list	*free_small_blocks;
	t_linked_list	*free_tiny_blocks;
	t_linked_list	*raw_blocks;
	size_t			page_size;
}					t_malloc_data;

typedef struct		s_zone
{
	char			type;
}					t_zone;

typedef struct		s_small_block
{
	uint32_t		size;
	char			free;
}					t_small_block;

typedef struct		s_tiny_block
{
	uint16_t		size;
	char			free;
}					t_tiny_block;

void				add_to_list(t_linked_list *list, void *elt);
t_linked_list		*new_linked_list(void);
void				*my_mmap(size_t size);
void				my_munmap(void *ptr, size_t size);
size_t				ft_strlen(char *str);
void				print_number(size_t number);
void				show_alloc_mem(void);

#endif