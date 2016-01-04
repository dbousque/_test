

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

t_node2	*sort_pile_determ2(t_pile *a)
{
	t_node2	*res;
	(void)a;
	res = NULL;
	return (res);
	/*t_node2	*res;
	t_pile	*pile_b;
	int		nb_elts_a;
	int		nb_elts_b;
	char	function;

	ft_putendl("NO BEST !");
	res = NULL;
	pile_b = empty_tree();
	while ((nb_elts_b = nb_elts(pile_b)) > 0 && !is_sorted_ab(pile_a, 1))
	{
		nb_elts_a = nb_elts(a);
		if (nb_elts_a > 1 && pile_a->elts[pile_a->top] > pile_a->elts[pile_a->top + 1])
			function = SA;
		else if (
	}*/
}
