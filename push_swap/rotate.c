

#include "push_swap.h"

void	rotate_a(t_pile *pile)
{
	int		tmp;
	int		tmp2;
	int		i;

	if (pile->length - pile->top > 1)
	{
		tmp = pile->elts[pile->length - 1];
		pile->elts[pile->length - 1] = pile->elts[pile->top];
		i = pile->length - 2;
		while (i >= pile->top)
		{
			tmp2 = pile->elts[i];
			pile->elts[i] = tmp;
			tmp = tmp2;
			i--;
		}
	}
}

void	rotate_b(t_pile *pile)
{
	rotate_a(pile);
}

void	rotate_ab(t_pile *pile_a, t_pile *pile_b)
{
	rotate_a(pile_a);
	rotate_b(pile_b);
}
