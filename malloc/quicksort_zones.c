

#include "malloc.h"

static int		get_nb_smaller(t_sort_zone *array, int start, int end,
							int (*cmp)(t_sort_zone *elt1, t_sort_zone *elt2))
{
	int		nb_smaller;
	int		i;

	nb_smaller = 0;
	i = start;
	while (i < end - 1)
	{
		if (cmp(&(array[i]), &(array[end - 1])) < 0)
			nb_smaller++;
		i++;
	}
	return (nb_smaller);
}

static void	swap_arr(t_sort_zone *array, int a, int z)
{
	t_sort_zone	tmp;

	tmp = array[a];
	array[a] = array[z];
	array[z] = tmp;
}

void	quicksort_zones(t_sort_zone *array, int start, int end,
							int (*cmp)(t_sort_zone *elt1, t_sort_zone *elt2))
{
	int		nb_smaller;
	int		a;
	int		z;

	if (end - start <= 1)
		return ;
	nb_smaller = get_nb_smaller(array, start, end, cmp);
	swap_arr(array, start + nb_smaller, end - 1);
	a = start;
	z = end - 1;
	while (1)
	{
		while (a < start + nb_smaller && cmp(&(array[a]), &(array[start + nb_smaller])) < 0)
			a++;
		if (a >= start + nb_smaller)
			break ;
		while (z > start + nb_smaller && cmp(&(array[z]), &(array[start + nb_smaller])) > 0)
			z--;
		if (z <= start + nb_smaller)
			break;
		swap_arr(array, a, z);
		a++;
		z--;
	}
	quicksort_zones(array, start, start + nb_smaller, cmp);
	quicksort_zones(array, start + nb_smaller + 1, end, cmp);
}