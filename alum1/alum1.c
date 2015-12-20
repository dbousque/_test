/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alum1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 20:17:28 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/20 15:44:52 by dbousque         ###   ########.fr       */
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
		ft_putchar('\n');
		i++;
	}
}

int		ft_intlen(int *board)
{
	int		i;

	i = 0;
	while (board[i])
		i++;
	return (i);
}

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

void	ft_putchars(char *take_last)
{
	int		i;

	i = 0;
	while (i < 2)
	{
		ft_putnbr(take_last[i]);
		ft_putchar('\n');
		i++;
	}
}

void	ft_putboard(int *board)
{
	int		i;
	int		x;

	i = 0;
	while (board[i])
	{
		x = 0;
		while (x < board[i])
		{
			ft_putchar('|');
			x++;
		}
		ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
}

int		get_player_move(int *error)
{
	char	*line;
	int		ret;

	ft_putstr("How many matches to take off : ");
	ret = get_next_line(0, &line);
	if (ret == -1)
	{
		*error = 1;
		return (ft_unexpected_error());
	}
	if (!(valid_line(line)))
		return (-1);
	ret = ft_atoi(line);
	return (ret);
}

void	make_player_move(int *board, int *current_last, int *error)
{
	int		input;
	int		go_on;

	input = 0;
	go_on = 1;
	while (go_on)
	{
		input = get_player_move(error);
		if (!(input > 3 || input < 1 || board[*current_last] < input))
			go_on = 0;
		if (go_on)
			ft_putendl("Bad input.");
	}
	board[*current_last] -= input;
	if (board[*current_last] == 0)
		(*current_last)--;
}

void	make_ai_move(int *board, char *take_last, int *current_last)
{
	int		nb;

	if (!take_last[*current_last])
		nb = (board[*current_last] - 1) % 4;
	else
		nb = board[*current_last] % 4;
	if (nb == 0)
		nb = 1;
	board[*current_last] -= nb;
	if (board[*current_last] == 0)
		(*current_last)--;
	ft_putstr("The AI took ");
	ft_putnbr(nb);
	if (nb == 1)
		ft_putendl(" match.");
	else
		ft_putendl(" matches.");
}

void	make_play(int *board, char *take_last, int current_last)
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
	{
		if (current_player == 1)
			ft_putendl("You won !");
		else
			ft_putendl("Sorry, the AI won.");
	}
}

int		ft_launch(char *filename, char stdinput)
{
	char	**file_content;
	int		*board;
	int		res;
	int		length;
	char	*take_last;

	file_content = NULL;
	res = get_file_content(filename, stdinput, &file_content, 1);
	if (res == -2)
		return (ft_unexpected_error());
	res = get_board(file_content, &board, &length);
	if (res == -1)
		return (ft_error());
	if (res == -2)
		return (ft_unexpected_error());
	if (!(take_last = get_take_last(board)))
		return (ft_unexpected_error());
	make_play(board, take_last, ft_intlen(board) - 1);
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
