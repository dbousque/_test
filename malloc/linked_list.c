

#include "malloc.h"

t_linked_list	new_linked_list(void)
{
	t_linked_list	list;

	list.size = getpagesize() / sizeof(void*);
	list.len = 0;
	list.elts = (void**)my_mmap(sizeof(void*) * list.size);
	return (list);
}

static void	double_list_size(t_linked_list *list)
{
	void	**new_elts;
	size_t	i;

	new_elts = (void**)my_mmap(sizeof(void*) * (list->size * 2));
	i = 0;
	while (i < list->len)
	{
		new_elts[i] = list->elts[i];
		i++;
	}
	my_munmap(list->elts, (sizeof(void*) * list->size));
	list->elts = new_elts;
	list->size *= 2;
}

void	add_to_list(t_linked_list *list, void *elt)
{
	if (list->len == list->size)
		double_list_size(list);
	list->elts[list->len] = elt;
	list->len++;
}