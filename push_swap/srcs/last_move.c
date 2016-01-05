/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:10:35 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 17:10:40 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	last_move(t_node2 *node)
{
	if (node->nb_moves <= 0)
		return (-1);
	return (node->previous_moves[node->nb_moves - 1]);
}

char	last_move_to_a(t_node2 *node)
{
	int		i;
	char	tmp;

	i = node->nb_moves - 1;
	while (i >= 0)
	{
		tmp = node->previous_moves[i];
		if (tmp == SA || tmp == SS || tmp == PA || tmp == PB
			|| tmp == RA || tmp == RR || tmp == RRA || tmp == RRR)
			return (tmp);
		i--;
	}
	return (-1);
}

char	last_move_to_b(t_node2 *node)
{
	int		i;
	char	tmp;

	i = node->nb_moves - 1;
	while (i >= 0)
	{
		tmp = node->previous_moves[i];
		if (tmp == SB || tmp == SS || tmp == PA || tmp == PB
			|| tmp == RB || tmp == RR || tmp == RRB || tmp == RRR)
			return (tmp);
		i--;
	}
	return (-1);
}
