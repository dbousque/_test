/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:23:46 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/08 20:53:10 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		ft_add_piece2(t_node2 *node, t_tetrimino *tetri, int x, int y)
{
	int		i_x;
	int		i_y;
	int		max;

	i_y = 0;
	while (i_y < tetri->heigth)
	{
		i_x = 0;
		while (i_x < tetri->width)
		{
			if (tetri->content[i_y][i_x] == '#')
			{
				if (i_y + y >= node->heigth)
					node->heigth = i_y + y + 1;
				if (i_x + x >= node->width)
					node->width = i_x + x + 1;
				node->board[i_y + y][i_x + x] = tetri->letter;
			}
			i_x++;
		}
		i_y++;
	}
	node->nb_pieces += 1;
	max = (node->heigth < node->width ? node->width : node->heigth);
	node->priority = 300 / max + node->nb_pieces * node->nb_pieces;
}

t_node2		*ft_new2(char **board, int heigth, int width, int nb_pieces)
{
	t_node2		*res;
	int			max;

	if (!(res = (t_node2*)malloc(sizeof(t_node2))))
		return (NULL);
	res->board = board;
	res->heigth = heigth;
	res->width = width;
	res->nb_pieces = nb_pieces;
	max = heigth;
	if (heigth < width)
		max = width;
	if (heigth == 0)
		res->priority = 0;
	else
		res->priority = 300 / max + nb_pieces * nb_pieces;
	return (res);
}

int			ft_bad_node(int max, t_node2 *hi, t_node2 *best, int cant)
{
	if ((max != -1 && (hi->width > max || hi->heigth > max)) || (cant
			&& !ft_could_be_closer(hi, best, max)))
		return (1);
	return (0);
}

t_node2		*ft_free_n_upd_max(t_node2 *best, t_node2 *high, int *max)
{
	ft_free_node(best);
	best = high;
	*max = best->width;
	if (*max < best->heigth)
		*max = best->heigth;
	return (best);
}
