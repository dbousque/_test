

#include "nm.h"

t_list	*new_list(void)
{
	t_list	*lst;

	lst = my_malloc(sizeof(t_list));
	lst->elts = my_malloc(sizeof(void*) * 32);
	lst->size = 32;
	lst->len = 0;
	return (lst);
}

void	double_list_size(t_list *lst)
{
	int		i;
	void	**new_elts;

	lst->size *= 2;
	new_elts = my_malloc(sizeof(void*) * lst->size);
	i = 0;
	while (i < lst->len)
	{
		new_elts[i] = lst->elts[i];
		i++;
	}
	lst->elts = new_elts;
}

void	add_to_list(t_list *lst, void *elt)
{
	if (lst->size == lst->len)
		double_list_size(lst);
	lst->elts[lst->len] = elt;
	lst->len++;
}