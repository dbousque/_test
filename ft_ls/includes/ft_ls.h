/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 13:59:55 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/13 19:20:59 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libdodo.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/xattr.h>
# include <sys/types.h>
# include <errno.h>
# include <stdio.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>

# define MINORBITS 20
# define MINORMASK ((1U << MINORBITS) - 1)
# define MAJOR(dev) ((unsigned int) ((dev) >> MINORBITS))
# define MINOR(dev) ((unsigned int) ((dev) & MINORMASK))

typedef struct	s_flags
{
	char		a;
	char		l;
	char		r;
	char		r_maj;
	char		t;
	char		g;
	char		d;
	char		u;
	char		s;
	char		a_maj;
	char		minus;
}				t_flags;

t_flags			*get_flags(int argc, char **argv, int *i);
void			quicksort(void **to_sort, int nb,
			int (*compare_fct)(void *elt1, void *elt2, void *elt3), void *elt3);
int				print_string_array_columns(char **strings, int nb, int nb_l,
																	int nb_per);
void			insertion_sort(void **to_sort, int nb,
			int (*compare_fct)(void *elt1, void *elt2, void *elt3), void *elt3);
void			print_file_size(struct stat *file_stats, int largest[6]);
void			print_type_n_rights(struct dirent *file,
									struct stat *file_stats, char *dir_name);
void			print_nb_hlinks(struct stat *file_stats, int largest);
int				illegal_option(char c);
void			print_file_owner(struct stat *file_stats, int largest,
																t_flags *flags);
void			print_group_name(struct stat *file_stats, int largest);
void			print_date(struct stat *file_stat, t_flags *flags);
char			*make_path(char *filename, char *dir_name);
void			print_errno(int error, char *filename);
void			*unexpected_error_null(void);
int				unexpected_error(void);
void			print_links_to(struct dirent *child, char *dir_name);
void			print_total(struct stat **file_stats, int nb, char *dir_name);
int				print_children_details(struct dirent **children,
										t_flags *flags, int nb, char *dir_name);
int				print_children_regular(struct dirent **children, int nb);
int				print_children_regular_std(struct dirent **children, int nb);
struct stat		**get_file_stats(struct dirent **children, char *dir_name,
														int largest[6], int nb);
void			sort_by_name(struct dirent **children, int nb);
void			sort_by_date(struct dirent **children, int nb, char *dir_name,
																		char l);
void			print_children(struct dirent **children, t_flags *flags,
												int nb_child, char *dir_name);
void			reverse_children(struct dirent **children, int len);
int				listdir(DIR *dir, t_flags *flags, char *dir_name,
														t_list *dir_children);
char			**list_to_string_array(t_list *params);
__uint8_t		get_d_type_from_stat(struct stat *stats);
int				print_params(char **dir_params, char **other_params,
												t_flags *flags, int nb_params);
int				print_dir_params(char **dir_params, t_flags *flags,
										char **other_params, char print_name);
int				print_other_params(char **other_params, t_flags *flags);
struct dirent	**strstr_to_dirent_array(char **params, int *l);
char			**get_params(int argc, char **argv, t_list **other_params,
																t_flags *flags);
int				strstrlen(char **strstr);
void			sort_by_size(struct dirent **children, int nb, char *dir_name);
int				ft_strcmp_child_name(void *elt1, void *elt2, void *elt3);
int				compare_by_date(void *elt1, void *elt2, void *elt3);
int				compare_by_access_date(void *elt1, void *elt2, void *elt3);
int				compare_sizes(void *elt1, void *elt2, void *elt3);

#endif
