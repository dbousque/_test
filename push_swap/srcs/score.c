/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:20:23 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 17:20:49 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		get_current_score(t_pile *pile_a, t_pile *pile_b)
{
	int		score;
	int		i;

	score = 0;
	i = pile_a->top;
	while (i < pile_a->length - 1)
	{
		if (pile_a->elts[i] > pile_a->elts[i + 1])
			score++;
		i++;
	}
	i = pile_b->top;
	while (i < pile_b->length - 1)
	{
		if (pile_b->elts[i] < pile_b->elts[i + 1])
			score++;
		i++;
	}
	score += nb_elts(pile_b);
	return (score);
}

char	is_sorted_ab(t_pile *pile, char is_a)
{
	int		i;

	i = pile->top;
	while (i < pile->length - 1)
	{
		if (is_a && pile->elts[i] > pile->elts[i + 1])
			return (0);
		else if (!is_a && pile->elts[i] < pile->elts[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int		best_score_min_index(int scores[11])
{
	int		i;
	int		best;

	best = 0;
	i = 1;
	while (i < 11)
	{
		if (scores[best] == -1 || (scores[i] != -1 && scores[i] < scores[best]))
			best = i;
		i++;
	}
	return (best);
}
