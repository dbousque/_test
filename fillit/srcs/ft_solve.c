/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 13:11:29 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/08 21:01:22 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tree		*ft_add_nodes(t_tree *tr, t_node2 *h, t_tetrimino **t, t_node2 *b)
{
	t_list		*points;
	t_list		*tmp;
	t_node2		*new;
	char		**board;
	int			max;

	board = h->board;
	max = -1;
	if (b)
		max = (b->width > b->heigth ? b->width : b->heigth);
	points = ft_ok_pnts(h, t[h->nb_pieces], max, b);
	tmp = points;
	while (tmp)
	{
		new = ft_new2(ft_strstrdup(board), h->heigth, h->width, h->nb_pieces);
		ft_add_piece2(new, t[h->nb_pieces],
				((t_point*)tmp->content)->x, ((t_point*)tmp->content)->y);
		tr = ft_add_to_tree2(tr, new);
		tmp = tmp->next;
	}
	if (points)
		ft_lstdel(&points, ft_del_points);
	ft_free_node(h);
	return (tr);
}

t_node2		*ft_complete(t_node2 *be, t_node2 *hi, int m_c[2], t_tetrimino **te)
{
	if (!be || (m_c[0] > hi->width && m_c[0] > hi->heigth))
	{
		be = ft_free_n_upd_max(be, hi, &(m_c[0]));
		m_c[1] = ft_has_min_size(te, m_c[0]);
	}
	else if (hi->width <= m_c[0] && hi->heigth <= m_c[0])
	{
		if (ft_could_be_closer(hi, be, m_c[0]))
			be = ft_free_n_upd_max(be, hi, &(m_c[0]));
		else
			ft_free_node(hi);
	}
	return (be);
}

void		ft_initialize(int *max, int *cannot)
{
	*max = -1;
	*cannot = 0;
}

t_node2		*ft_solve_board(t_tetrimino **tetris, t_tree *tree)
{
	t_node2	*highest;
	int		max;
	int		cannot_closer;
	int		max_cannot[2];
	t_node2	*best_so_far;

	best_so_far = NULL;
	ft_initialize(&max, &cannot_closer);
	while (tree->last > 0)
	{
		highest = ft_get_top(tree);
		if (ft_bad_node(max, highest, best_so_far, cannot_closer))
			ft_free_node(highest);
		else if (!tetris[highest->nb_pieces])
		{
			max_cannot[0] = max;
			max_cannot[1] = cannot_closer;
			best_so_far = ft_complete(best_so_far, highest, max_cannot, tetris);
			cannot_closer = max_cannot[1];
			max = max_cannot[0];
		}
		else
			tree = ft_add_nodes(tree, highest, tetris, best_so_far);
	}
	return (best_so_far);
}

char		**ft_solve_tetris(t_tetrimino **tetris)
{
	char	**board;
	int		maxes[2];
	int		i;
	t_tree	*tree;
	t_node2	*res;

	i = 0;
	maxes[0] = tetris[0]->width;
	maxes[1] = tetris[0]->heigth;
	while (tetris[i])
	{
		maxes[0] += tetris[i]->width;
		maxes[1] += tetris[i]->heigth;
		i++;
	}
	board = ft_allocate_strstr(maxes[0], maxes[1], '.');
	if (!board)
		return (NULL);
	tree = ft_empty_tree();
	tree = ft_add_to_tree2(tree, ft_new2(ft_strstrdup(board), 0, 0, 0));
	res = ft_solve_board(tetris, tree);
	board = ft_rip_res(res->board, tetris);
	return (board);
}
