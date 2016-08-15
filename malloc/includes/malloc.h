/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:51:43 by dbousque          #+#    #+#             */
/*   Updated: 2016/08/15 14:22:42 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

# define ALLOC 1
# define FREE 2
# define PRINT_MEM 3
# define REALLOC 4
# define DUMP_HEXA 5
# define DUMP_FREE 6
# define CALLOC 7
# define REALLOCF 8
# define HELP 9
# define NB_PAGES_PER_SMALL_ZONE 128
# define NB_PAGES_PER_TINY_ZONE 16
# define MAX_SMALL_BLOCK 4000
# define MAX_TINY_BLOCK 255
# define TINY 1
# define SMALL 2
# define LARGE 3
# define N NULL

typedef struct			s_linked_list
{
	void				**elts;
	size_t				size;
	size_t				len;
}						t_linked_list;

typedef struct			s_malloc_data
{
	t_linked_list		zones;
	t_linked_list		free_small_blocks;
	t_linked_list		free_tiny_blocks;
	t_linked_list		raw_blocks;
	size_t				page_size;
	char				debug_alloc;
	char				debug_print;
	char				print_calls;
	char				show_at_each_turn;
}						t_malloc_data;

typedef struct			s_zone
{
	char				type;
}						t_zone;

typedef struct			s_sort_zone
{
	char				type;
	void				*zone;
}						t_sort_zone;

typedef struct			s_small_block
{
	uint32_t			size;
	char				free;
}						t_small_block;

typedef struct			s_tiny_block
{
	uint16_t			size;
	char				free;
}						t_tiny_block;

typedef t_malloc_data	t_md;

pthread_mutex_t			g_lock;

char					get_debug(int opt);
void					*malloc(size_t size);
void					malloc_help(void);
void					malloc_help2(void);
void					*realloc(void *ptr, size_t size);
void					free(void *ptr);
void					malloc_dump(void);
void					*reallocf(void *ptr, size_t size);
void					*my_realloc(t_malloc_data *data, void *ptr,
										size_t size, char *invalid_pointer);
void					*my_reallocf(t_malloc_data *data, void *ptr,
																size_t size);
void					*my_calloc(t_malloc_data *data, size_t size);
void					*my_malloc(t_malloc_data *data, size_t size);
void					my_free(t_malloc_data *data, void *ptr);
void					*realloc_small(t_malloc_data *data, void *p_nx_b[2],
													void *ptr, size_t size);
void					*realloc_tiny(t_malloc_data *data, void *p_nx_b[2],
													void *ptr, size_t size);
void					*my_mmap(size_t size);
void					my_munmap(void *ptr, size_t size);
void					*handle_malloc_option(size_t size, char option,
																void *ptr);
size_t					get_next_pagesize(size_t size);
void					*alloc_new_block(t_malloc_data *data, size_t size);
void					*alloc_tiny(t_malloc_data *data, size_t size);
void					*alloc_small(t_malloc_data *data, size_t size);
void					add_new_free_tiny_block(t_malloc_data *data,
													void *start, size_t size);
void					add_new_free_small_block(t_malloc_data *data,
													void *start, size_t size);
void					free_small(t_malloc_data *data, void *ptr,
										void *prev_block, void *next_block);
void					free_tiny(t_malloc_data *data, void *ptr,
										void *prev_block, void *next_block);
char					is_allocated_small_adress(t_malloc_data *data,
				void *ptr, t_small_block *start, void **prev_next_block[2]);
char					is_allocated_tiny_adress(t_malloc_data *data,
				void *ptr, t_tiny_block *start, void **prev_next_block[2]);
size_t					is_raw_block(t_malloc_data *data, void *ptr);
void					print_mem(t_malloc_data *data);
size_t					get_small_zone_size(t_malloc_data *data);
size_t					get_tiny_zone_size(t_malloc_data *data);
void					remove_free_small_block(t_malloc_data *data,
																size_t ind);
void					remove_free_tiny_block(t_malloc_data *data,
																size_t ind);
size_t					ind_of_small_block(t_malloc_data *data, void *ptr);
size_t					ind_of_tiny_block(t_malloc_data *data, void *ptr);
void					memcopy(void *from, void *to, size_t nb);
void					free_small(t_malloc_data *data, void *ptr,
										void *prev_block, void *next_block);
void					free_tiny(t_malloc_data *data, void *ptr,
										void *prev_block, void *next_block);
size_t					get_zone_type(t_malloc_data *data, void *ptr,
										void **prev_block, void **next_block);
void					add_to_list(t_linked_list *list, void *elt);
t_linked_list			new_linked_list(void);
void					*my_mmap(size_t size);
void					my_munmap(void *ptr, size_t size);
size_t					ft_strlen(char *str);
void					print_number(size_t number);
void					print_number_fd(size_t number, int fd);
void					print_address(void *ptr);
void					print_address_fd(void *ptr, int fd);
void					show_alloc_mem(void);
void					print_malloc_call(char option, void *ptr, size_t size);
void					print_malloc_return(char option, void *ptr);
void					print_debug_free_null(void);
void					print_debug_free_raw(void *ptr, size_t size);
void					print_debug_bad_free(void *ptr);
void					print_debug_free_small(t_malloc_data *data, void *ptr,
																size_t size);
void					print_debug_free_tiny(t_malloc_data *data, void *ptr,
																size_t size);
void					print_debug_realloc_raw(void *ptr, size_t start_size,
															size_t end_size);
void					print_debug_realloc_small(t_malloc_data *data,
								void *ptr, size_t start_size, size_t end_size);
void					print_debug_realloc_tiny(t_malloc_data *data,
								void *ptr, size_t start_size, size_t end_size);
void					print_debug_malloc(size_t size, void *ptr);
void					print_ft_ntoa_base(size_t n, char *base);
void					print_ft_ntoa_base_fd(size_t n, char *base, int fd);
void					quicksort_zones(t_sort_zone *array, int start, int end,
							int (*cmp)(t_sort_zone *elt1, t_sort_zone *elt2));
size_t					print_raw_zone(void *zone);
size_t					print_small_zone(t_malloc_data *data, void *zone);
size_t					print_tiny_zone(t_malloc_data *data, void *zone);
void					print_byte(void *ptr);
void					malloc_dump_hexa(t_malloc_data *data);
void					dump_hexa_raw(void *zone);
void					dump_hexa_small(t_malloc_data *data, void *zone);
void					dump_hexa_tiny(t_malloc_data *data, void *zone);
void					dump_hexa(void *ptr, size_t size);
void					malloc_free_zones(void);
void					malloc_dump_free(t_malloc_data *data);
void					ft_putstr(char *str);
void					ft_putstr_fd(char *str, int fd);

#endif
