

#include "push_swap.h"

void	swap_a(t_pile *pile)
{
	int		tmp;

	if (pile->length - pile->top > 1)
	{
		tmp = pile->elts[pile->top];
		pile->elts[pile->top] = pile->elts[pile->top + 1];
		pile->elts[pile->top + 1] = tmp;
	}
}

void	swap_b(t_pile *pile)
{
	swap_a(pile);
}

void	swap_ab(t_pile *pile_a, t_pile *pile_b)
{
	swap_a(pile_a);
	swap_b(pile_b);
}
