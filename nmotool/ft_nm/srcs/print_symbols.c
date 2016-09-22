/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:03:27 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:21:17 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_symbols(t_list *symbols, char *stringtable, t_flags *options,
																char *file_name)
{
	int		i;

	i = 0;
	while (i < symbols->len)
	{
		if (((t_symbol*)symbols->elts[i])->exec_type == BITS_64)
			maybe_launch_64(symbols->elts[i], stringtable, file_name, options);
		else if (((t_symbol*)symbols->elts[i])->exec_type == BITS_32)
			maybe_launch_32(symbols->elts[i], stringtable, file_name, options);
		i++;
	}
}

int		cmp_by_numeric(void *elt1, void *elt2)
{
	t_symbol	*sym1;
	t_symbol	*sym2;

	sym1 = elt1;
	sym2 = elt2;
	if (sym1->exec_type == BITS_64)
	{
		if (((struct nlist_64*)sym1->symbol)->n_value >
				((struct nlist_64*)sym2->symbol)->n_value)
			return (1);
		if (((struct nlist_64*)sym1->symbol)->n_value ==
				((struct nlist_64*)sym2->symbol)->n_value)
			return (0);
		return (-1);
	}
	if (((struct nlist*)sym1->symbol)->n_value >
			((struct nlist*)sym2->symbol)->n_value)
		return (1);
	if (((struct nlist*)sym1->symbol)->n_value ==
			((struct nlist*)sym2->symbol)->n_value)
		return (0);
	return (-1);
}

int		cmp_strs(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (str1[i] > str2[i])
		return (1);
	else if (str1[i] == str2[i])
		return (0);
	return (-1);
}

int		cmp_by_name(void *elt1, void *elt2)
{
	t_symbol	*sym1;
	t_symbol	*sym2;
	char		*name1;
	char		*name2;
	char		*stringtable;

	stringtable = get_stringtable();
	sym1 = elt1;
	sym2 = elt2;
	if (sym1->exec_type == BITS_32)
	{
		name1 = &(stringtable[((struct nlist*)sym1->symbol)->n_un.n_strx]);
		name2 = &(stringtable[((struct nlist*)sym2->symbol)->n_un.n_strx]);
	}
	else
	{
		name1 = &(stringtable[((struct nlist_64*)sym1->symbol)->n_un.n_strx]);
		name2 = &(stringtable[((struct nlist_64*)sym2->symbol)->n_un.n_strx]);
	}
	return (cmp_strs(name1, name2));
}

void	sort_symbols(t_list *symbols, t_flags *options)
{
	if (!options->p)
		my_mergesort(symbols->elts, 0, symbols->len, cmp_by_numeric);
	if (!options->p && !options->n)
		my_mergesort(symbols->elts, 0, symbols->len, cmp_by_name);
	if (!options->p && options->r)
		reverse_list(symbols);
}
