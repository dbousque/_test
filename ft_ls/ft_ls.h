/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 13:59:55 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/12 17:02:31 by dbousque         ###   ########.fr       */
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
	char		minus;
}				t_flags;

t_flags			*get_flags(int argc, char **argv, int *i);
void			quicksort(void **to_sort, int nb,
			int (*compare_fct)(void *elt1, void *elt2, void *elt3), void *elt3);
int				print_string_array_columns(char **strings, int nb);
void			insertion_sort(void **to_sort, int nb,
			int (*compare_fct)(void *elt1, void *elt2, void *elt3), void *elt3);
void			print_date(struct stat *file_stats);
void			print_file_size(struct stat *file_stats, int largest[6]);
void			print_type_n_rights(struct dirent *file,
									struct stat *file_stats, char *dir_name);
void			print_nb_hlinks(struct stat *file_stats, int largest);
void			print_file_owner(struct stat *file_stats, int largest);
void			print_group_name(struct stat *file_stats, int largest);
void			print_date(struct stat *file_stats);
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
void			sort_by_date(struct dirent **children, int nb, char *dir_name);

#endif
