

#include "nm.h"

void	simple_sort(void **elts, int start, int end,
									int (*cmp)(void *elt1, void *elt2))
{
	int		i;
	int		j;
	void	*tmp;

	i = end;
	while (i > 1)
	{
		j = start;
		while (j < i - 1)
		{
			if (cmp(elts[j], elts[j + 1]) > 0)
			{
				tmp = elts[j];
				elts[j] = elts[j + 1];
				elts[j + 1] = tmp;
			}
			j++;
		}
		i--;
	}
}