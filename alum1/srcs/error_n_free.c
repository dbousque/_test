/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_n_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/20 16:54:04 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/20 16:54:19 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alum1.h"

void	free_vars(char **file_content, int *board, char *take_last)
{
	int		i;

	if (board)
		free(board);
	board = NULL;
	if (take_last)
		free(take_last);
	take_last = NULL;
	i = 0;
	while (file_content && file_content[i])
	{
		free(file_content[i]);
		file_content[i] = NULL;
		i++;
	}
	if (file_content)
		free(file_content);
	file_content = NULL;
}

void	ft_error(char **file_content, int *board, char *take_last)
{
	free_vars(file_content, board, take_last);
	ft_putendl_fd("ERROR", 2);
}

void	ft_unexpected_error(char **file_content, int *board, char *take_last)
{
	free_vars(file_content, board, take_last);
	ft_putendl_fd("unexpected error (file not found, malloc error...)", 2);
}
