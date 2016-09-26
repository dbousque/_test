/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 17:59:35 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/26 17:52:53 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

char	*handle_stringtable(char *ptr, char option)
{
	static char		*str = NULL;

	if (option == 1)
		str = ptr;
	return (str);
}

char	already_in_rans(t_list *rans, struct ranlib *ran)
{
	int		i;

	i = 0;
	while (i < rans->len)
	{
		if (cmp_rans(rans->elts[i], ran) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	print_defined_symb_64(struct nlist_64 *symbol, struct section *sect)
{
	print_hexa_n(symbol->n_value, 16);
	ft_putstr(" ");
	print_defined_symbol_type_64(symbol, sect);
	ft_putstr(" ");
}
