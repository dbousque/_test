

#include "push_swap.h"

void	free_pile(t_pile *pile)
{
	if (pile)
	{
		free(pile->elts);
		pile->elts = NULL;
		free(pile);
		pile = NULL;
	}
}

void	put_pile(t_pile *pile)
{
	int		i;

	i = pile->length - 1;
	while (i >= pile->top)
	{
		if (i != pile->length - 1)
			ft_putstr(", ");
		ft_putnbr(pile->elts[i]);
		i--;
	}
	ft_putchar('\n');
}

void	double_pile_length(t_pile *pile)
{
	int		*ori;
	int		i;
	int		half;

	half = pile->length;
	pile->length *= 2;
	ori = pile->elts;
	if ((pile->elts = (int*)malloc(sizeof(int) * pile->length)))
	{
		i = 0;
		while (i < half)
		{
			pile->elts[i + half] = ori[i];
			i++;
		}
		pile->top += half;
	}
	free(ori);
	ori = NULL;
}

char	put_on_pile(t_pile *pile, int nb)
{
	if (pile->top <= 0)
		double_pile_length(pile);
	if (!pile || !pile->elts)
		return (-1);
	pile->top--;
	pile->elts[pile->top] = nb;
	return (0);
}

int		take_from_pile(t_pile *pile)
{
	if (pile->length - pile->top > 0)
	{
		pile->top++;
		return (pile->elts[pile->top - 1]);
	}
	return (0);
}
