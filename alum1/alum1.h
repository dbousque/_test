/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alum1.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 20:18:06 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/19 22:09:18 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALUM1_H
# define ALUM1_H

# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>

int		get_board(char **file_cont, int **board, int *len);
int		get_file_content(char *filename, char stdinput, char ***file);

#endif
