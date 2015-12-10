/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optimization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:26:01 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/08 11:43:33 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			ft_can_put(char **board, int x, int y, t_tetrimino *tetri)
{
	int		i_x;
	int		i_y;

	i_y = y;
	while (i_y < y + tetri->heigth && board[i_y])
	{
		i_x = x;
		while (i_x < x + tetri->width && board[i_y][i_x])
		{
			if (board[i_y][i_x] != '.'
				&& tetri->content[i_y - y][i_x - x] == '#')
				return (0);
			i_x++;
		}
		if (!board[i_y][i_x] && x != i_x - tetri->width)
			return (0);
		i_y++;
	}
	if (!board[i_y] && i_y != y + (y + tetri->heigth - 1))
		return (0);
	return (1);
}

char		ft_l(int *one, int *two, char ind1, char ind2)
{
	int		i;

	if (ind1 >= 0 || ind2 >= 0)
	{
		i = 0;
		while (i < 26)
		{
			if (one[i] == 0 || two[i] == 0)
				return (-1);
			if (one[i] < two[i])
				return (1);
			if (one[i] > two[i])
				return (0);
			i++;
		}
	}
	return (-1);
}

int			ft_could_be_closer(t_node2 *n, t_node2 *b, int max)
{
	int		o[26];
	int		t[26];
	int		y;
	int		x;

	if (n->heigth > max || n->width > max)
		return (0);
	ft_void_int(o);
	ft_void_int(t);
	y = 0;
	while (y < max)
	{
		x = -1;
		while (++x < max)
		{
			if (b->board[y][x] != '.' && t[b->board[y][x] - 'A'] == 0)
				t[b->board[y][x] - 'A'] = y * max + x + 1;
			if (n->board[y][x] != '.' && o[n->board[y][x] - 'A'] == 0)
				o[n->board[y][x] - 'A'] = y * max + x + 1;
			if (ft_l(o, t, n->board[y][x] - 'A', b->board[y][x] - 'A') >= 0)
				return (ft_l(o, t, n->board[y][x] - 'A', b->board[y][x] - 'A'));
		}
		y++;
	}
	return (0);
}

int			ft_has_min_size(t_tetrimino **tetris, int max)
{
	int		nb_tetris;
	int		min_carre;

	nb_tetris = 0;
	while (tetris[nb_tetris])
		nb_tetris++;
	nb_tetris *= 4;
	min_carre = 2;
	while (min_carre * min_carre < nb_tetris)
		min_carre++;
	if (min_carre == max)
		return (1);
	return (0);
}
