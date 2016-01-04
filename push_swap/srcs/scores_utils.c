/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scores_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/02 18:51:51 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 18:52:21 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	calculate_moves_score(t_pile *a, t_pile *b, int scores[11])
{
	int		i;

	i = 0;
	while (i < 11)
	{
		if (i == 0 && nb_elts(a) > 1)
		{
			scores[i] = apply_function_and_cancel(a, b, swap_a, swap_a);
		}
		else if (i == 1 && nb_elts(b) > 1)
		{
			scores[i] = apply_function_and_cancel(a, b, swap_b, swap_b);
		}
		else if (i == 2 && nb_elts(a) > 1 && nb_elts(b) > 1)
			scores[i] = apply_function_and_cancel(a, b, swap_ab, swap_ab);
		else if (i == 3 && nb_elts(b) > 0)
			scores[i] = apply_function_and_cancel(a, b, push_a, push_b);
		else if (i == 4 && nb_elts(a) > 0)
			scores[i] = apply_function_and_cancel(a, b, push_b, push_a);
		else if (i == 5 && nb_elts(a) > 2)
			scores[i] = apply_function_and_cancel(a, b, rotate_a, reverse_rotate_a);
		else if (i == 6 && nb_elts(b) > 2)
			scores[i] = apply_function_and_cancel(a, b, rotate_b, reverse_rotate_b);
		else if (i == 7 && nb_elts(a) > 2 && nb_elts(b) > 2)
			scores[i] = apply_function_and_cancel(a, b, rotate_ab, reverse_rotate_ab);
		else if (i == 8 && nb_elts(a) > 2)
			scores[i] = apply_function_and_cancel(a, b, reverse_rotate_a, rotate_a);
		else if (i == 9 && nb_elts(b) > 2)
			scores[i] = apply_function_and_cancel(a, b, reverse_rotate_b, rotate_b);
		else if (i == 10 && nb_elts(a) > 2 && nb_elts(b) > 2)
			scores[i] = apply_function_and_cancel(a, b, reverse_rotate_ab, rotate_ab);
		i++;
	}
}

void	void_scores(int scores[11])
{
	int		i;

	i = 0;
	while (i < 11)
	{
		scores[i] = -1;
		i++;
	}
}

void	print_scores(int scores[11])
{
	int		i;

	i = 0;
	while (i < 11)
	{
		ft_printf("%d : %d\n", i, scores[i]);
		i++;
	}
}

int		best_score_index(int scores[11])
{
	int		i;
	int		best;

	best = 0;
	i = 1;
	while (i < 11)
	{
		if (scores[i] > scores[best])
			best = i;
		i++;
	}
	return (best);
}
