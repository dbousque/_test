/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 18:16:03 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/26 18:16:05 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MALLOC_H
# define MY_MALLOC_H

# include <stdlib.h>

# define MALLOC 1
# define FREE 2
# define STD_ALLOC 4096 * 4096
# define STD_NB_ZONES 64
# define MMAP_MODE 0

typedef struct	s_zone
{
	void		*start;
	void		*current;
	void		*end;
}				t_zone;

typedef struct	s_zone_list
{
	t_zone		*elts;
	int			len;
	int			size;
}				t_zone_list;

void			*my_malloc(size_t size);
void			free_all(void);
void			double_allocs_size(t_zone_list *allocs, char *error);
void			free_list(t_zone_list *allocs);
void			*my_mmap(size_t size);
void			my_munmap(void *ptr, size_t size);

#endif
