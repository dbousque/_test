/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 13:59:55 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/09 14:41:12 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libdodo.h"
# include <dirent.h>
# include <sys/stat.h>

typedef struct	s_flags
{
	char		a;
	char		l;
	char		r;
	char		r_maj;
	char		t;
	DIR			*dir;
}				t_flags;

#endif
