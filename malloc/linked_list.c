

#include "malloc.h"
#include <stdio.h>
t_linked_list	*new_linked_list(void)
{
	t_linked_list	*list;

	list = (t_linked_list*)my_mmap(sizeof(t_linked_list));
	if (!list)
		return (NULL);
	list->size = getpagesize() / sizeof(void*);
	list->len = 0;
	list->elts = (void**)my_mmap(sizeof(void*) * list->size);
	printf("initial size : %ld\n", sizeof(void*) * list->size);
	return (list);
}

static void	double_list_size(t_linked_list *list)
{
	void	**new_elts;
	size_t	i;

	printf("	list->elts location BEFORE : %p\n", list->elts);
	//printf("new size : %ld\n", sizeof(void*) * (list->size * 2));
	new_elts = (void**)my_mmap(sizeof(void*) * (list->size * 2));
	i = 0;
	while (i < list->len)
	{
		new_elts[i] = list->elts[i];
		i++;
	}
	//printf("LA : %ld\n", (sizeof(void*) * list->size) / getpagesize());
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