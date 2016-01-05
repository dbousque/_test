/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_best.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:01:03 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 17:02:45 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	remove_two_moves(t_node2 *node, int ind)
{
	int		i;

	node->previous_moves[ind] = '\0';
	node->previous_moves[ind + 1] = '\0';
	i = ind + 2;
	while (i < node->nb_moves)
	{
		node->previous_moves[i - 2] = node->previous_moves[i];
		i++;
	}
	node->nb_moves -= 2;
}

t_node2	*reduce_best(t_node2 *node)
{
	int		i;

	i = 0;
	while (i < node->nb_moves - 1)
	{
		if (looping_moves(node->previous_moves[i + 1], node->previous_moves[i]))
		{
			remove_two_moves(node, i);
			i--;
		}
		else
			i++;
	}
	return (node);
}
