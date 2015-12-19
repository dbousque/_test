/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alum1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 20:17:28 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/19 22:08:44 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alum1.h"

int		ft_error(void)
{
	ft_putendl_fd("ERROR", 2);
	return (0);
}

int		ft_unexpected_error(void)
{
	ft_putendl_fd("unexpected error (file not found, malloc error...)", 2);
	return (0);
}

void	ft_putintint(int *board)
{
	int		i;

	i = 0;
	while (board[i])
	{
		ft_putnbr(board[i]);
		i++;
	}
}

int		ft_launch(char *filename, char stdinput)
{
	char	**file_content;
	int		*board;
	int		res;
	int		length;

	file_content = NULL;
	res = get_file_content(filename, stdinput, &file_content);
	if (res == -2)
		return (ft_unexpected_error());
	res = get_board(file_content, &board, &length);
	if (res == -1)
		return (ft_error());
	if (res == -2)
		return (ft_unexpected_error());
	ft_putintint(board);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc == 1)
		return (ft_launch("", 1));
	else if (argc == 2)
		return (ft_launch(argv[1], 0));
	ft_putendl("Format : ./alum1 <filename> or ./alum1");
	return (0);
}
