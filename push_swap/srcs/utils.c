/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/02 18:29:43 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 18:32:32 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		nb_elts(t_pile *pile)
{
	return (pile->length - pile->top);
}

char	is_sorted(t_pile *pile)
{
	int		i;

	i = pile->top;
	while (i < pile->length - 1)
	{
		if (pile->elts[i] >= pile->elts[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int		get_score_pile_b(t_pile *pile_b)
{
	int		i;
	int		j;
	int		score;

	score = 0;
	i = pile_b->top;
	while (i < pile_b->length - 1)
	{
		j = i + 1;
		while (j < pile_b->length)
		{
			if (pile_b->elts[i] > pile_b->elts[j])
				score += j - i;
			j++;
		}
		i++;
	}
	return (score);
}

int		get_current_score2(t_pile *pile_a, t_pile *pile_b)
{
	int		score;
	int		i;
	int		j;

	score = 0;
	i = pile_a->top;
	while (i < pile_a->length - 1)
	{
		j = i + 1;
		while (j < pile_a->length)
		{
			if (pile_a->elts[i] < pile_a->elts[j])
				score += j - i;
			j++;
		}
		i++;
	}
	score += get_score_pile_b(pile_b);
	return (score);
}
