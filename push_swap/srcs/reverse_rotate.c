/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:19:49 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 17:19:51 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate_a(t_pile *pile, t_pile *unused)
{
	int		tmp;
	int		tmp2;
	int		i;

	(void)unused;
	if (pile->length - pile->top > 1)
	{
		tmp = pile->elts[pile->top];
		pile->elts[pile->top] = pile->elts[pile->length - 1];
		i = pile->top + 1;
		while (i <= pile->length - 1)
		{
			tmp2 = pile->elts[i];
			pile->elts[i] = tmp;
			tmp = tmp2;
			i++;
		}
	}
}

void	reverse_rotate_b(t_pile *unused, t_pile *pile)
{
	reverse_rotate_a(pile, unused);
}

void	reverse_rotate_ab(t_pile *pile_a, t_pile *pile_b)
{
	reverse_rotate_a(pile_a, pile_b);
	reverse_rotate_b(pile_a, pile_b);
}
