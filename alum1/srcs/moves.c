/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/20 16:52:07 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/20 17:29:41 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alum1.h"

int		get_player_move(int *error)
{
	char	*line;
	int		ret;

	ft_putstr("How many matches to take off : ");
	ret = get_next_line(0, &line);
	if (ret == -1)
		*error = 1;
	else
	{
		if (!(valid_line(line)))
			return (-1);
		ret = ft_atoi(line);
	}
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
