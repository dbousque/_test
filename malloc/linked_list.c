

#include "malloc.h"

t_linked_list	*new_linked_list(void)
{
	t_linked_list	*list;

	list = my_mmap(sizeof(t_linked_list));
	list->elts = my_mmap(sizeof(void*) * 16);
	list->size = 16;
	list->len = 0;
	return (list);
}

static void	double_list_size(t_linked_list *list)
{
	void	**new_elts;
	size_t	i;

	new_elts = my_mmap(sizeof(void*) * (list->size * 2));
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

void	print_zone(t_zone *zone)
{
	char	*tmp_str;

	tmp_str = "  - number of allocated blocks : ";
	write(1, tmp_str, ft_strlen(tmp_str));
	print_number(zone->nb_used_blocks);
	write(1, "\n", 1);
	tmp_str = "  - type of zone : ";
	write(1, tmp_str, ft_strlen(tmp_str));
	if (zone->type == TINY)
		tmp_str = "TINY";
	else if (zone->type == SMALL)
		tmp_str = "SMALL";
	else if (zone->type == LARGE)
		tmp_str = "LARGE";
	else
		tmp_str = "UNKNOWN TYPE!";
	write(1, tmp_str, ft_strlen(tmp_str));
	write(1, "\n", 1);
}

void	print_zones(t_linked_list *zones)
{
	size_t	i;
	char	*tmp_str;

	tmp_str = "Printing zones : \n";
	write(1, tmp_str, ft_strlen(tmp_str));
	i = 0;
	while (i < zones->len)
	{
		tmp_str = "\nZone : \n";
		write(1, tmp_str, ft_strlen(tmp_str));
		print_zone(zones->elts[i]);
		i++;
	}
}