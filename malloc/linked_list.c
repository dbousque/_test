

#include "malloc.h"
#include <stdio.h>
t_linked_list	*new_linked_list(void)
{
	t_linked_list	*list;

	list = (t_linked_list*)my_mmap(sizeof(t_linked_list));
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

	//printf("	list->elts location BEFORE : %p\n", list->elts);
	//printf("new size : %ld\n", sizeof(void*) * (list->size * 2));
	new_elts = (void**)my_mmap(sizeof(void*) * (list->size * 2));
	i = 0;
	while (i < list->size * 2)
	{
		new_elts[i] = list->elts[i];
		i++;
	}
	//printf("LA\n");
	my_munmap((void*)*list->elts, (sizeof(void*) * list->size));
	//printf("LA AUSSI\n");
	list->elts = new_elts;
	list->size *= 2;
	//printf("	list->elts location after : %p\n", list->elts);
}

void	add_to_list(t_linked_list *list, void *elt)
{
	if (list->len == list->size)
		double_list_size(list);
	//printf("ADDING\n");
	//fflush(stdout);
	list->elts[list->len] = elt;
	//printf("AFTER ADDING\n");
	//fflush(stdout);
	list->len++;
}

/*void	print_zone(t_zone *zone)
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
}*/