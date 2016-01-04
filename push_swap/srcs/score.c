

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

/*int		find_min_index(t_pile *pile_a)
{
	int		min;
	int		i;

	i = pile_a->top;
	min = -1;
	while (i < pile_a->length)
	{
		if (min == -1 || pile_a->elts[i] < pile_a->elts[min])
			min = i;
		i++;
	}
	return (min);
}

int		get_current_score(t_pile *pile_a, t_pile *pile_b)
{
	int		score;
	int		min;
	int		i;
	int		to_add;

	min = find_min_index(pile_a);
	i = min;
	score = 0;
	if (min != -1)
	{
		ft_printf("min : %d, top : %d\n", min, pile_a->top);
		to_add = -(pile_a->top - min);
		ft_printf("to_add : %d\n", to_add);
		while (i > pile_a->top)
		{
			if (pile_a->elts[i] < pile_a->elts[i - 1])
				score++;
			i--;
		}
		i = min;
		while (i < pile_a->length - 1)
		{
			if (pile_a->elts[i] > pile_a->elts[i + 1])
				score++;
			i++;
		}
	}
	min = find_min_index(pile_b);
	if (min != -1)
	{
		to_add += -(pile_b->top - min);
		i = min;
		while (i > pile_b->top)
		{
			if (pile_b->elts[i] > pile_b->elts[i - 1])
				score++;
			i--;
		}
		i = min;
		while (i < pile_b->length - 1)
		{
			if (pile_b->elts[i] < pile_b->elts[i + 1])
				score++;
			i++;
		}
	}
	score *= 2;
	ft_putstr("A : ");
	put_pile(pile_a);
	ft_putstr("B : ");
	put_pile(pile_b);
	ft_printf("Score : {red}%d{eoc}\n\n", score);
	sleep(5);
	return (score + to_add);
}*/

