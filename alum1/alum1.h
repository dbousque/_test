/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alum1.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 20:18:06 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/20 17:01:49 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALUM1_H
# define ALUM1_H

# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>

int		get_board(char **file_cont, int **board, int *len);
int		get_file_content(char *filename, char stdinp, char ***file, char goon);
char	valid_line(char *line);
void	ft_putintint(int *board);
int		ft_intlen(int *board);
void	free_vars(char **file_content, int *board, char *take_last);
void	ft_error(char **file_content, int *board, char *take_last);
void	ft_unexpected_error(char **file_content, int *board, char *take_last);
void	ft_putboard(int *board);
int		get_player_move(int *error);
void	make_player_move(int *board, int *current_last, int *error);
void	make_ai_move(int *board, char *take_last, int *current_last);

#endif
