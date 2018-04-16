

#include "libjson.h"

void	print_n_tabs(int n)
{
	while (n > 0)
	{
		ft_putstr("  ");
		n--;
	}
}

void	print_dict(t_value *elt, int nb_tabs)
{
	int		i;

	i = 0;
	ft_putstr("{\n");
	while (((t_dict*)elt->data)->keys[i])
	{
		print_n_tabs(nb_tabs + 1);
		ft_putchar('"');
		ft_putstr(((t_dict*)elt->data)->keys[i]);
		ft_putstr("\": ");
		print_elt(((t_dict*)elt->data)->values[i], nb_tabs + 1, 0);
		if (((t_dict*)elt->data)->keys[i + 1])
			ft_putchar(',');
		ft_putchar('\n');
		i++;
	}
	print_n_tabs(nb_tabs);
	ft_putstr("}\n");
}

void	print_array(t_value *elt, int nb_tabs)
{
	int		i;

	i = 0;
	ft_putstr("[\n");
	while (((t_value**)elt->data)[i])
	{
		print_elt(((t_value**)elt->data)[i], nb_tabs + 1, 1);
		if (((t_value**)elt->data)[i + 1])
			ft_putchar(',');
		ft_putchar('\n');
		i++;
	}
	print_n_tabs(nb_tabs);
	ft_putstr("]\n");
}

void	print_elt(t_value *elt, int nb_tabs, char print_tabs)
{
	if (print_tabs)
		print_n_tabs(nb_tabs);
	if (elt->type == DICT)
		print_dict(elt, nb_tabs);
	else if (elt->type == ARRAY)
		print_array(elt, nb_tabs);
	else if (elt->type == STRING)
	{
		ft_putchar('"');
		ft_putstr((char*)elt->data);
		ft_putchar('"');
	}
	else if (elt->type == LONG)
		ft_printf("%ld", *((long*)elt->data));
	else if (elt->type == DOUBLE)
		ft_printf("%f", *((double*)elt->data));
	else if (elt->type == BOOLEAN)
		ft_putstr(*((char*)elt->data) == 1 ? "true" : "false");
}

void	print_json(t_value *json)
{
	print_elt(json, 0, 1);
}