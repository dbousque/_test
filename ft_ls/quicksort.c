

#include "ft_ls.h"

void	rebuild_to_sort(void **to_sort, void **part1, void **part2, int nb1, int nb2, void *pivot)
{
	int		i;
	int		decal;

	i = 0;
	while (i < nb1)
	{
		to_sort[i] = part1[i];
		i++;
	}
	to_sort[i] = pivot;
	decal = i + 1;
	i = 0;
	while (i < nb2)
	{
		to_sort[decal + i] = part2[i];
		i++;
	}
}

char	is_sorted(void **to_sort, int nb,
			int (*compare_fct)(void *elt1, void *elt2, void *elt3), void *elt3)
{
	nb--;
	while (nb > 0)
	{
		if (compare_fct(to_sort[nb], to_sort[nb - 1], elt3) > 0)
			return (0);
		nb--;
	}
	return (1);
}

void	quicksort(void **to_sort, int nb,
			int (*compare_fct)(void *elt1, void *elt2, void *elt3), void *elt3)
{
	void	*part1[nb];
	void	*part2[nb];
	void	*pivot;
	int		nb1;
	int		nb2;

	if (nb <= 1 || is_sorted(to_sort, nb, compare_fct, elt3))
		return ;
	pivot = to_sort[nb - 1];
	nb -= 2;
	nb1 = 0;
	nb2 = 0;
	while (nb >= 0)
	{
		if (compare_fct(pivot, to_sort[nb], elt3) < 0)
		{
			part1[nb1] = to_sort[nb];
			nb1++;
		}
		else
		{
			part2[nb2] = to_sort[nb];
			nb2++;
		}
		nb--;
	}
	quicksort(part1, nb1, compare_fct, elt3);
	quicksort(part2, nb2, compare_fct, elt3);
	rebuild_to_sort(to_sort, part1, part2, nb1, nb2, pivot);
}

void	insertion_sort(void **to_sort, int nb,
			int (*compare_fct)(void *elt1, void *elt2, void *elt3), void *elt3)
{
	int		i;
	int		j;
	void	*tmp;

	i = 1;
	if (nb == 1)
		return ;
	while (i < nb)
	{
		j = i;
		while (j > 0 && compare_fct(to_sort[j], to_sort[j - 1], elt3) > 0)
		{
			tmp = to_sort[j];
			to_sort[j] = to_sort[j - 1];
			to_sort[j - 1] = tmp;
			j--;
		}
		i++;
	}
}
