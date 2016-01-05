/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:26:45 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 17:32:20 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	update_node(t_node2 *node, char move, int get_score)
{
	apply_function(node->pile_a, node->pile_b, move);
	node->nb_moves++;
	node->previous_moves[node->nb_moves - 1] = move;
	if (get_score)
	{
		node->score = get_current_score(node->pile_a, node->pile_b);
		node->priority = priority_function(node->score, node->nb_moves);
	}
}

void	add_new_nodes(t_tree *tree, t_node2 *top, int scores[11])
{
	int		i;
	t_node2	*to_add;

	i = 0;
	while (i < 11)
	{
		if (scores[i] != -1 && !looping_nodes(top, i))
		{
			to_add = ft_new_node(top->pile_a, top->pile_b,
									top->nb_moves, top->previous_moves);
			update_node(to_add, i, 1);
			tree = ft_add_to_tree2(tree, to_add);
		}
		i++;
	}
}

char	possible_best(t_node2 *top, t_node2 *best_so_far)
{
	if (!best_so_far)
		return (1);
	if (best_so_far->nb_moves > top->nb_moves)
		return (1);
	return (0);
}

int		inner_loop(t_node2 *top, t_node2 **best, int scores[11], t_tree *tree)
{
	if (nb_elts(top->pile_b) == 0 && is_sorted_ab(top->pile_a, 1))
		*best = top;
	else
	{
		void_scores(scores);
		calculate_moves_score(top->pile_a, top->pile_b, scores);
		add_new_nodes(tree, top, scores);
		free_node(top);
	}
	return (1);
}

t_node2	*sort_pile_tree(t_pile *pile_a)
{
	t_tree	*tree;
	t_node2	*top;
	t_node2	*best_so_far;
	int		scores[11];
	int		i;

	i = 0;
	best_so_far = NULL;
	tree = ft_empty_tree();
	tree = ft_add_to_tree2(tree, ft_new_node(pile_a, empty_pile(), 0, NULL));
	while (tree->last > 0)
	{
		top = ft_get_top(tree);
		if (possible_best(top, best_so_far))
			i += inner_loop(top, &best_so_far, scores, tree);
		else
			free_node(top);
		if (i % 20000 == 0)
		{
			free_tree(tree);
			return (best_so_far);
		}
	}
	free_tree(tree);
	return (best_so_far);
}
