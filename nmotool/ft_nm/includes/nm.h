/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 18:15:54 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/26 18:15:56 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <unistd.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach/machine.h>
# include <mach-o/ranlib.h>
# include <ar.h>

# include "my_malloc.h"

# define BITS_64 1
# define BITS_32 2
# define MACH_O_64 1
# define MACH_O_32 2
# define FAT 3

typedef struct		s_list
{
	void			**elts;
	int				len;
	int				size;
}					t_list;

typedef struct		s_symbol
{
	char			exec_type;
	void			*symbol;
	void			*sect;
	void			*seg;
}					t_symbol;

typedef struct		s_flags
{
	char			g;
	char			n;
	char			o;
	char			p;
	char			r;
	char			u;
	char			u_maj;
	char			j;
}					t_flags;

size_t				ft_strlen(char *str);
void				ft_putstr(char *str);
void				print_error(char *str);
void				print_format(void);
void				print_error_file(char *str, char *filename);
void				print_hexa_n(size_t numb, int n);
void				print_n_char(char c, int n);
t_list				*new_list(void);
void				add_to_list(t_list *lst, void *elt);
struct section_64	*get_n_sect_64(void *ptr, size_t n,
											struct segment_command_64 **seg);
struct section		*get_n_sect_32(void *ptr, size_t n,
												struct segment_command **seg);
void				*bad_executable_null(void);
void				set_valid_pointer(void *start, void *end);
char				valid_pointer(void *ptr);
void				reset_valid_pointer(void);
void				bad_executable(void);
void				handle_file(char *ptr, char type, char *file_name);
void				print_symbol_64(t_symbol *symb, char *stringtable,
														t_flags *options);
void				print_symbol_32(t_symbol *symb, char *stringtable,
														t_flags *options);
char				match_sect_name_with_type(char *seg_name, char *sect_name);
void				print_local_or_ext_64(struct nlist_64 *symbol, char c);
void				print_local_or_ext_32(struct nlist *symbol, char c);
t_list				*get_mach_o_32_symbols(void *ptr, char **stringtable);
t_list				*get_mach_o_64_symbols(void *ptr, char **stringtable);
t_list				*get_fat_symbols(void *ptr, char **stringtable);
void				*get_fat_start(void *ptr, size_t *res_size, size_t size);
void				nm(char *ptr, size_t size, char *file_name);
char				ft_streq(char *str1, char *str2);
void				ft_putstrn(char *str, int n);
int					ft_atoi(const char *str);
void				*get_big_endian(char *ptr, size_t size);
void				sort_list(t_list *list, int (*cmp)(void *elt1, void *elt2));
void				quicksort(void **array, int start, int end,
										int (*cmp)(void *elt1, void *elt2));
void				handle_ranlib(void *ptr, size_t size, char *file_name);
size_t				end_of_name(char *str);
char				*get_current_ar_name(char *ptr);
int					cmp_rans(void *elt1, void *elt2);
void				clear_options(void);
void				void_options(t_flags *options);
int					read_options(int argc, char **argv, t_flags *options);
void				*get_current_options(void);
void				set_current_options(void *ptr);
char				*get_stringtable(void);
void				reverse_list(t_list *list);
void				simple_sort(void **elts, int start, int end,
									int (*cmp)(void *elt1, void *elt2));
void				my_mergesort(void **elts, int start, int end,
									int (*cmp)(void *elt1, void *elt2));
int					display_help(void);
char				is_ranlib(char *ptr);
void				clear_options_and_free_all(void);
void				set_current_options(void *ptr);
void				*get_current_options(void);
void				*get_set_options_handler(void *ptr, char option);
void				print_symbols(t_list *symbols, char *stringtable,
									t_flags *options, char *file_name);
void				maybe_launch_32(t_symbol *symbol, char *stringtable,
										char *file_name, t_flags *options);
void				maybe_launch_64(t_symbol *symbol, char *stringtable,
										char *file_name, t_flags *options);
void				sort_symbols(t_list *symbols, t_flags *options);
char				*handle_stringtable(char *ptr, char option);
char				already_in_rans(t_list *rans, struct ranlib *ran);
void				print_defined_symb_64(struct nlist_64 *symbol,
														struct section *sect);
void				print_defined_symbol_type_64(struct nlist_64 *symbol,
														struct section *sect);

#endif
