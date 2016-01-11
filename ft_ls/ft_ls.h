/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 13:59:55 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/11 18:00:54 by dbousque         ###   ########.fr       */
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

#endif
