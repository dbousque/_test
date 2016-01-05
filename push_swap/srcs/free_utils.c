/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:41:17 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 17:41:19 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_node(t_node2 *node)
{
	if (node)
	{
		free(node->pile_a);
		free(node->pile_b);
		node->pile_a = NULL;
		node->pile_b = NULL;
		free(node->previous_moves);
		node->previous_moves = NULL;
		free(node);
		node = NULL;
	}
}

void	free_tree(t_tree *tree)
{
	int		i;

	i = 1;
	while (i <= tree->last)
	{
		free_node(tree->tree[i]);
		tree->tree[i] = NULL;
		i++;
	}
	free(tree);
	tree = NULL;
}
