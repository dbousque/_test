

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
		previous_moves[length] = *((char*)(tmp->content));
		length++;
		tmp = tmp->next;
	}
	//ft_lstdel(&list, lst_del);
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

int		next_unsorted_b(t_pile *pile)
{
	int		i;
	int		min_ind;

	min_ind = min_index(pile);
	if (min_ind == -1)
		return (-1);
	i = pile->top;
	while (i < min_ind - 1)
	{
		if (pile->elts[i] < pile->elts[i + 1])
			return (i);
		i++;
	}
	i = min_ind;
	while (i < pile->length - 1)
	{
		if (pile->elts[i] < pile->elts[i + 1])
			return (i);
		i++;
	}
	if (min_ind > pile->top)
	{
		if (pile->elts[pile->top] > pile->elts[pile->length -1])
			return (pile->length - 1);
	}
	return (-1);
}

void	put_next_unsorted_on_top(t_pile *a, int next_unsorted, t_list **list, t_list **list_end)
{
	int		val;
	char	car;

	val = a->elts[next_unsorted];
	if (next_unsorted - a->top > nb_elts(a) / 2)
	{
		car = RRA;
		while (a->elts[a->top] != val)
		{
			ft_lstaddend(list_end, ft_lstnew(&car, sizeof(char)));
			if (!(*list))
				*list = *list_end;
			apply_function(a, NULL, RRA);
		}
	}
	else
	{
		car = RA;
		while (a->elts[a->top] != val)
		{
			ft_lstaddend(list_end, ft_lstnew(&car, sizeof(char)));
			if (!(*list))
				*list = *list_end;
			apply_function(a, NULL, RA);
		}
	}
}

void	put_min_on_top(t_pile *pile, t_list **list, t_list **list_end)
{
	int		min_ind;

	min_ind = min_index(pile);
	put_next_unsorted_on_top(pile, min_ind, list, list_end);
}

void	sort_a(t_pile *a, t_list **list, t_list **list_end)
{
	int		next_unsort;
	char	sa;

	sa = SA;
	while (!(is_sorted_ab(a, 1)))
	{
		next_unsort = next_unsorted(a);
		if (next_unsort > a->top)
			put_next_unsorted_on_top(a, next_unsort, list, list_end);
		if (next_unsort != -1)
		{
			ft_lstaddend(list_end, ft_lstnew(&sa, sizeof(char)));
			if (!(*list))
				*list = *list_end;
			apply_function(a, NULL, SA);
		}
		else
			put_min_on_top(a, list, list_end);
	}
}

void	sort_b(t_pile *b, t_list **list, t_list **list_end)
{
	int		next_unsort;
	char	sa;

	sa = SA;
	while (!(is_sorted_ab(b, 0)))
	{
		next_unsort = next_unsorted_b(b);
		if (next_unsort > b->top)
			put_next_unsorted_on_top(b, next_unsort, list, list_end);
		if (next_unsort != -1)
		{
			ft_lstaddend(list_end, ft_lstnew(&sa, sizeof(char)));
			if (!(*list))
				*list = *list_end;
			apply_function(b, NULL, SA);
		}
		else
			put_min_on_top(b, list, list_end);
	}
}

void	make_function(t_pile *a, t_pile *b, t_list **list_end, char func)
{
	apply_function(a, b, func);
	ft_lstaddend(list_end, ft_lstnew(&func, sizeof(char)));
}

int		last_to_push_into_nb_to_consider_a(t_pile *a, int nb_to_consider, int pivot)
{
	int		i;
	int		last;

	i = 1;
	last = 0;
	while (i < nb_to_consider)
	{
		if (a->elts[i + a->top] < pivot)
			last = i;
		i++;
	}
	return (last);
}

int		last_to_push_into_nb_to_consider_b(t_pile *b, int nb_to_consider, int pivot)
{
	int		i;
	int		last;

	i = 1;
	last = 0;
	while (i < nb_to_consider)
	{
		if (b->elts[i + b->top] > pivot)
			last = i;
		i++;
	}
	return (last);
}

int		push_smaller_to_b(t_pile *a, t_pile *b, t_list **list_end, int nb_consider_pivot[2])
{
	int		nb_pushed;
	int		i;
	int		nb_to_consider;
	int		pivot;

	pivot = nb_consider_pivot[1];
	nb_to_consider = nb_consider_pivot[0];
	i = 0;
	nb_pushed = 0;
	while (i < nb_to_consider)
	{
		if (a->elts[a->top] < pivot)
		{
			nb_pushed++;
			make_function(a, b, list_end, PB);
		}
		else
			make_function(a, b, list_end, RA);
		i++;
	}
	return (nb_pushed);
}

int		push_higher_to_a(t_pile *a, t_pile *b, t_list **list_end, int nb_consider_pivot[2])
{
	int		nb_pushed;
	int		i;
	int		nb_to_consider;
	int		pivot;

	pivot = nb_consider_pivot[1];
	nb_to_consider = nb_consider_pivot[0];
	i = 0;
	nb_pushed = 0;
	while (i < nb_to_consider)
	{
		if (b->elts[b->top] > pivot)
		{
			nb_pushed++;
			make_function(a, b, list_end, PA);
		}
		else
			make_function(a, b, list_end, RB);
		i++;
	}
	return (nb_pushed);
}

void	return_to_ori_position_a(t_pile *a, t_list **list_end, int to_ret)
{
	int		i;

	i = 0;
	while (i < to_ret)
	{
		make_function(a, NULL, list_end, RRA);
		i++;
	}
}

void	return_to_ori_position_b(t_pile *b, t_list **list_end, int to_ret)
{
	int		i;

	i = 0;
	while (i < to_ret)
	{
		make_function(NULL, b, list_end, RRB);
		i++;
	}
}

void	restore_a(t_pile *a, t_pile *b, t_list **list_end, int nb_pushed)
{
	while (nb_pushed > 0)
	{
		make_function(a, b, list_end, PA);
		nb_pushed--;
	}
}

void	restore_b(t_pile *a, t_pile *b, t_list **list_end, int nb_pushed)
{
	while (nb_pushed > 0)
	{
		make_function(a, b, list_end, PB);
		nb_pushed--;
	}
}

void	quicksort_a(t_pile *a, t_pile *b, t_list **list_end, int nb_to_consider)
{
	int		pivot;
	int		nb_pushed;
	int		nb_consider_pivot[2];

	nb_pushed = 0;
	if (nb_elts(a) > 1 && nb_to_consider > 1)
	{
		pivot = a->elts[a->top];
		make_function(a, b, list_end, RA);
		nb_to_consider--;
		nb_consider_pivot[0] = nb_to_consider;
		nb_consider_pivot[1] = pivot;
		nb_pushed = push_smaller_to_b(a, b, list_end, nb_consider_pivot);
		return_to_ori_position_a(a, list_end, nb_to_consider - nb_pushed);
	}
	if (nb_to_consider - nb_pushed > 1)
		quicksort_a(a, b, list_end, nb_to_consider - nb_pushed);
	if (nb_elts(a) > 1)
		make_function(a, b, list_end, RRA);
	if (nb_pushed > 1)
		quicksort_b(a, b, list_end, nb_pushed);
	restore_a(a, b, list_end, nb_pushed);
}

void	quicksort_b(t_pile *a, t_pile *b, t_list **list_end, int nb_to_consider)
{
	int		pivot;
	int		nb_pushed;
	int		nb_consider_pivot[2];

	nb_pushed = 0;
	if (nb_elts(b) > 1 && nb_to_consider > 1)
	{
		pivot = b->elts[b->top];
		make_function(a, b, list_end, RB);
		nb_to_consider--;
		nb_consider_pivot[0] = nb_to_consider;
		nb_consider_pivot[1] = pivot;
		nb_pushed = push_higher_to_a(a, b, list_end, nb_consider_pivot);
		return_to_ori_position_b(b, list_end, nb_to_consider - nb_pushed);
	}
	if (nb_to_consider - nb_pushed > 1)
		quicksort_b(a, b, list_end, nb_to_consider - nb_pushed);
	if (nb_elts(b) > 1)
		make_function(a, b, list_end, RRB);
	if (nb_pushed > 1)
		quicksort_a(a, b, list_end, nb_pushed);
	restore_b(a, b, list_end, nb_pushed);
}

t_node2	*sort_pile_determ2(t_pile *pile_a)
{
	t_pile	*b;
	t_pile	*a;
	t_list	*list;
	t_list	*list_end;
	char	car;

	car = SA;
	list = NULL;
	list_end = NULL;
	if (!(a = copy_pile(pile_a)))
		return (NULL);
	b = empty_pile();
	ft_lstaddend(&list_end, ft_lstnew(&car, sizeof(char)));
	list = list_end;
	quicksort_a(a, b, &list_end, nb_elts(a));
	list = list->next;
	ft_putstr("A : ");
	put_pile(a);
	ft_putstr("B : ");
	put_pile(b);
	return (list_to_node(list, a, b));
}

t_node2	*sort_pile_determ3(t_pile *pile_a)
{
	t_pile	*a;
	t_list	*list;
	t_list	*list_end;

	list = NULL;
	list_end = NULL;
	if (!(a = copy_pile(pile_a)))
		return (NULL);
	sort_a(a, &list, &list_end);
	return (list_to_node(list, a, NULL));
}

/*t_node2	*sort_pile_determ2(t_pile *pile_a)
{
	t_pile	*b;
	t_pile	*a;
	int		next_unsort;
	t_list	*list;
	t_list	*list_end;
	char	sa;

	list = NULL;
	list_end = NULL;
	sa = SA;
	if (!(a = copy_pile(pile_a)))
		return (NULL);
	b = empty_pile();
	while (!(nb_elts(b) == 0 && is_sorted_ab(a, 1)))
	{
		next_unsort = next_unsorted(a);
		if (next_unsort > a->top)
			put_next_unsorted_on_top(a, next_unsort, &list, &list_end);
		if (next_unsort != -1)
		{
			ft_lstaddend(&list_end, ft_lstnew(&sa, sizeof(char)));
			if (!list)
				list = list_end;
			apply_function(a, b, SA);
		}
		else
			put_min_on_top(a, &list, &list_end);
	}
	return (list_to_node(list, a, b));
}*/
