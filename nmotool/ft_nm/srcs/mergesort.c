

#include "nm.h"

void	rep_tmp(void **elts, int start, int end, void **tmp)
{
	int		i;

	i = start;
	while (i < end)
	{
		elts[i] = tmp[i - start];
		i++;
	}
}

void	merge(void **elts, int start, int end,
									int (*cmp)(void *elt1, void *elt2))
{
	void	*tmp[end - start];
	int		i;
	int		j;
	int		x;

	x = 0;
	i = start;
	j = start + ((end - start) / 2);
	while (1)
	{
		if (i == start + ((end - start) / 2) && j == end)
			break ;
		while (i < start + ((end - start) / 2)
				&& (j == end || cmp(elts[i], elts[j]) <= 0))
		{
			tmp[x] = elts[i];
			x++;
			i++;
		}
		while (j < end && (i == start + ((end - start) / 2)
					|| cmp(elts[j], elts[i]) < 0))
		{
			tmp[x] = elts[j];
			x++;
			j++;
		}
	}
	rep_tmp(elts, start, end, tmp);
}

void	my_mergesort(void **elts, int start, int end,
									int (*cmp)(void *elt1, void *elt2))
{
	if (end - start <= 1)
		return ;
	my_mergesort(elts, start, start + ((end - start) / 2), cmp);
	my_mergesort(elts, start + ((end - start) / 2), end, cmp);
	merge(elts, start, end, cmp);
}