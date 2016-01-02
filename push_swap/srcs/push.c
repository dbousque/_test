

#include "push_swap.h"

void	push_a(t_pile *pile_a, t_pile *pile_b)
{
	if (pile_b->length - pile_b->top > 0)
		put_on_pile(pile_a, take_from_pile(pile_b));
}

void	push_b(t_pile *pile_a, t_pile *pile_b)
{
	push_a(pile_b, pile_a);
}
