/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alum1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 20:17:28 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/20 19:09:20 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alum1.h"

char	*get_take_last(int *board)
{
	char	*res;
	int		i;

	if (!(res = (char*)malloc(sizeof(char) * ft_intlen(board))))
		return (NULL);
	res[0] = 0;
	i = 1;
	while (board[i])
	{
		if (board[i - 1] % 4 == 1)
			res[i] = (res[i - 1] == 0 ? 1 : 0);
		else
			res[i] = (res[i - 1] == 0 ? 0 : 1);
		i++;
	}
	return (res);
}

void	putwinner(int current_player)
{
	if (current_player == 1)
		ft_putendl("You won !");
	else
		ft_putendl("Sorry, the AI won.");
}

int		make_play(int *board, char *take_last, int current_last)
{
	char	current_player;
	int		error;

	error = 0;
	current_player = 1;
	while (board[0] > 0 && !error)
	{
		if (current_player == 1)
			ft_putendl("\n_____________\nYour turn : \n");
		else
			ft_putendl("\n_____________\nAI's turn : \n");
		ft_putboard(board);
		if (current_player == 1)
			make_player_move(board, &current_last, &error);
		else
			make_ai_move(board, take_last, &current_last);
		current_player *= -1;
	}
	if (!error)
		putwinner(current_player);
	return (error);
}

void	ft_launch(char *filename, char stdinput)
{
	char	**file_content;
	int		*board;
	int		res;
	char	*take_last;

	take_last = NULL;
	board = NULL;
	file_content = NULL;
	res = get_file_content(filename, stdinput, &file_content, 1);
	if (res == -2)
		ft_unexpected_error(file_content, board, take_last);
	else
	{
		res = get_board(file_content, &board);
		if (res == -1)
			ft_error(file_content, board, take_last);
		else if (res == -2 || !(take_last = get_take_last(board)))
			ft_unexpected_error(file_content, board, take_last);
		else if ((res = make_play(board, take_last, ft_intlen(board) - 1)) == 1)
			ft_unexpected_error(file_content, board, take_last);
		else
			free_vars(file_content, board, take_last);
	}
}

int		main(int argc, char **argv)
{
	if (argc == 1)
		ft_launch("", 1);
	else if (argc == 2)
		ft_launch(argv[1], 0);
	else
		ft_putendl("Format : ./alum1 <filename> or ./alum1");
	return (0);
}
