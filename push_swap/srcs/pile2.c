

#include "push_swap.h"

t_pile	*empty_pile(void)
{
	t_pile	*res;

	if (!(res = (t_pile*)malloc(sizeof(t_pile))))
		return (NULL);
	res->length = 1;
	res->top = 1;
	if (!(res->elts = (int*)malloc(sizeof(int))))
		return (NULL);
	return (res);
}

t_pile	*pile_from_array(int *nbs, int length)
{
	t_pile	*res;
	int		i;

	i = length - 1;
	res = empty_pile();
	while (i >= 0)
	{
		if (put_on_pile(res, nbs[i]) == -1)
			return (NULL);
		i--;
	}
	return (res);
}
