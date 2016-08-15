

#include "my_malloc.h"

void	free_list(t_zone_list *allocs)
{
	size_t	i;

	if (allocs->size)
	{
		i = 0;
		while (i < allocs->len)
		{
			free(allocs->elts[i].start);
			i++;
		}
	}
}

void	double_allocs_size(t_zone_list *allocs, char *error)
{
	t_zone	*new_elts;
	size_t	i;

	if (!(new_elts = malloc(allocs->size * 2)))
	{
		*error = 1;
		return ;
	}
	i = 0;
	while (i < allocs->len)
	{
		new_elts[i] = allocs->elts[i];
		i++;
	}
	free(allocs->elts);
	allocs->elts = new_elts;
	allocs->size *= 2;
}