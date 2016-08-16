

#include "my_malloc.h"


	 #include <stdio.h>

char	alloc_new_zone(t_zone_list *allocs)
{
	char	error;

	error = 0;
	if (allocs->len == allocs->size)
		double_allocs_size(allocs, &error);
	if (error || !(allocs->elts[allocs->len].start = malloc(STD_ALLOC)))
	{
		printf("ERROR\n");
		fflush(stdout);
		return (0);
	}
	printf("malloc : %p\n", allocs->elts[allocs->len].start);
	fflush(stdout);
	allocs->elts[allocs->len].current = allocs->elts[allocs->len].start;
	allocs->elts[allocs->len].end = allocs->elts[allocs->len].start + STD_ALLOC;
	allocs->len++;
	return (1);
}

void	*malloc_list(t_zone_list *allocs, size_t size)
{
	if (!allocs->size)
	{
		if (!(allocs->elts = malloc(sizeof(t_zone) * STD_NB_ZONES)))
			return (NULL);
		allocs->len = 0;
		allocs->size = STD_NB_ZONES;
	}
	if (allocs->elts[allocs->len - 1].current
						+ size < allocs->elts[allocs->len - 1].end)
	{
		allocs->elts[allocs->len - 1].current += size;
		return (allocs->elts[allocs->len - 1].current - size);
	}
	while (!(alloc_new_zone(allocs)))
		continue ;
	return (malloc_list(allocs, size));
}

void	*handle_malloc(char option, size_t size)
{
	static t_zone_list	allocs = {NULL, 0, 0};

	if (option == MALLOC)
		return (malloc_list(&allocs, size));
	else if (option == FREE)
		free_list(&allocs);
	return (NULL);
}

void	*my_malloc(size_t size)
{
	return (handle_malloc(MALLOC, size));
}

void	free_all(void)
{
	handle_malloc(FREE, 0);
}