/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 13:35:57 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/08 11:48:34 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define BUF_SIZE 64

typedef struct		s_file
{
	int				fd;
	char			*content;
}					t_file;

int					get_next_line(int const fd, char **line);

#endif
