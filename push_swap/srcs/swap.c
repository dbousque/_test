

#include "push_swap.h"

void	swap_a(t_pile *pile, t_pile *unused)
{
	int		tmp;

	(void)unused;
	if (pile->length - pile->top > 1)
	{
		tmp = pile->elts[pile->top];
		pile->elts[pile->top] = pile->elts[pile->top + 1];
		pile->elts[pile->top + 1] = tmp;
	}
}

void	swap_b(t_pile *unused, t_pile *pile)
{
	swap_a(pile, unused);
}

void	swap_ab(t_pile *pile_a, t_pile *pile_b)
{
	swap_a(pile_a, pile_b);
	swap_b(pile_a, pile_b);
}
