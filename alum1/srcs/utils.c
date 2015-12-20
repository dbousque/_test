/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/20 16:55:04 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/20 17:46:00 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alum1.h"

int		intmax_in_board(int *board)
{
	int		max;
	int		i;

	max = board[0];
	i = 1;
	while (board[i])
	{
		if (board[i] > max)
			max = board[i];
		i++;
	}
	return (max);
}

void	print_n_spaces(int n)
{
	while (n > 0)
	{
		ft_putchar(' ');
		n--;
	}
}

void	ft_putboard(int *board)
{
	int		i;
	int		x;
	int		max;

	max = intmax_in_board(board);
	i = 0;
	while (board[i])
	{
		print_n_spaces((max - board[i]) / 2 + 3);
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
