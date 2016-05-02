

#include "utils.h"

static void		malloc_error(void)
{
	printf("Could not allocate memory\n");
	exit(1);
}

t_linked_list	*new_list(void)
{
	t_linked_list	*res;

	if (!(res = (t_linked_list*)malloc(sizeof(t_linked_list))))
		malloc_error();
	if (!(res->elts = (void**)malloc(sizeof(void*) * 2)))
		malloc_error();
	res->len = 0;
	res->size = 2;
	return (res);
}

static void		double_list_size(t_linked_list *list)
{
	int		i;
	void	**new_elts;

	list->size *= 2;
	if (!(new_elts = (void**)malloc(sizeof(void*) * list->size)))
		malloc_error();
	i = 0;
	while (i < list->len)
	{
		new_elts[i] = list->elts[i];
		i++;
	}
	free(list->elts);
	list->elts = new_elts;
}

void	add_to_list(t_linked_list *list, void *elt)
{
	if (list->len == list->size)
		double_list_size(list);
	list->elts[list->len] = elt;
	list->len++;
}