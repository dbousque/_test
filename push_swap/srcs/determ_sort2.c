

#include "push_swap.h"

t_node2	*list_to_node(t_list *list, t_pile *a, t_pile *b)
{
	t_node2	*res;
	t_list	*tmp;
	int		length;
	char	*previous_moves;

	if (!(res = (t_node2*)malloc(sizeof(t_node2))))
		return (NULL);
	tmp = list;
	length = 0;
	while (tmp)
	{
		length++;
		tmp = tmp->next;
	}
	res->nb_moves = length;
	res->pile_a = a;
	res->pile_b = b;
	if (!(previous_moves = (char*)malloc(sizeof(char) * length)))
		return (NULL);
	length = 0;
	tmp = list;
	while (tmp)
	{
		previous_moves[length] = (char)((tmp->content));
		length++;
		tmp = tmp->next;
	}
	ft_lstdel(&list, lst_del);
	res->previous_moves = previous_moves;
	return (res);
}

int		min_index(t_pile *pile)
{
	int		i;
	int		min;

	min = -1;
	i = pile->top;
	while (i < pile->length)
	{
		if (min == -1 || pile->elts[i] < pile->elts[min])
			min = i;
		i++;
	}
	return (min);
}

int		next_unsorted(t_pile *pile)
{
	int		i;
	int		min_ind;

	min_ind = min_index(pile);
	if (min_ind == -1)
		return (-1);
	i = pile->top;
	while (i < min_ind - 1)
	{
		if (pile->elts[i] > pile->elts[i + 1])
			return (i);
		i++;
	}
	i = min_ind;
	while (i < pile->length - 1)
	{
		if (pile->elts[i] > pile->elts[i + 1])
			return (i);
		i++;
	}
	if (min_ind > pile->top)
	{
		if (pile->elts[pile->top] < pile->elts[pile->length -1])
			return (pile->length - 1);
	}
	return (-1);
}

void	put_next_unsorted_on_top(t_pile *a, int next_unsorted)
{
	int		val;

	val = a->elts[next_unsorted];
	if (next_unsorted - a->top > nb_elts(a) / 2)
	{
		while (a->elts[a->top] != val)
			apply_function(a, NULL, RRA);
	}
	else
	{
		while (a->elts[a->top] != val)
			apply_function(a, NULL, RA);
	}
}

void	put_min_on_top(t_pile *pile)
{
	int		min_ind;

	min_ind = min_index(pile);
	put_next_unsorted_on_top(pile, min_ind);
}

t_node2	*sort_pile_determ2(t_pile *a)
{
	t_node2	*res;
	t_pile	*b;
	int		nb_elts_a;
	int		nb_elts_b;
	int		next_unsort;

	res = NULL;
	b = empty_pile();
	while (!((nb_elts_b = nb_elts(b)) == 0 && is_sorted_ab(a, 1)))
	{
		nb_elts_a = nb_elts(a);
		next_unsort = next_unsorted(a);
		if (next_unsort > a->top)
			put_next_unsorted_on_top(a, next_unsort);
		ft_putstr("A BEFORE : ");
		put_pile(a);
		if (next_unsort != -1)
			apply_function(a, b, SA);
		else
			put_min_on_top(a);
		ft_putstr("A AFTER  : ");
		put_pile(a);
	}
	return (res);
}
