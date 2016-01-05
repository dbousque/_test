/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   looping_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 16:03:31 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 17:13:19 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	looping_nodes2(int best, char last_move_a, char last_move_b)
{
	if (best == RR && (last_move_a == RRR
			|| last_move_a == RRA || last_move_b == RRB))
		return (1);
	if (best == RRA && (last_move_a == RA
			|| last_move_a == RR))
		return (1);
	if (best == RRB && (last_move_b == RB
			|| last_move_b == RR))
		return (1);
	if (best == RRR && (last_move_a == RR
			|| last_move_a == RA || last_move_b == RB))
		return (1);
	return (0);
}

char	looping_nodes(t_node2 *top, int best)
{
	char	last_move_a;
	char	last_move_b;

	last_move_a = last_move_to_a(top);
	last_move_b = last_move_to_b(top);
	if (best == SA && (last_move_a == SA || last_move_a == SS))
		return (1);
	if (best == SB && (last_move_b == SB || last_move_b == SS))
		return (1);
	if (best == SS && (last_move_a == SS
			|| last_move_a == SA || last_move_b == SB))
		return (1);
	if (best == PA && last_move_a == PB)
		return (1);
	if (best == PB && last_move_b == PA)
		return (1);
	if (best == RA && (last_move_a == RRA || last_move_a == RRR))
		return (1);
	if (best == RB && (last_move_b == RRB || last_move_b == RRR))
		return (1);
	return (looping_nodes2(best, last_move_a, last_move_b));
}

char	looping_moves(char current_move, char last_move)
{
	if (current_move == SA && last_move == SA)
		return (1);
	if (current_move == SB && last_move == SB)
		return (1);
	if (current_move == SS && last_move == SS)
		return (1);
	if (current_move == PA && last_move == PB)
		return (1);
	if (current_move == PB && last_move == PA)
		return (1);
	if (current_move == RA && last_move == RRA)
		return (1);
	if (current_move == RB && last_move == RRB)
		return (1);
	if (current_move == RR && last_move == RRR)
		return (1);
	if (current_move == RRA && last_move == RA)
		return (1);
	if (current_move == RRB && last_move == RB)
		return (1);
	if (current_move == RRR && last_move == RR)
		return (1);
	return (0);
}
