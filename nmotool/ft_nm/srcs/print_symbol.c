/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 17:53:31 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:20:48 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_defined_symbol_type_64(struct nlist_64 *symbol,
													struct section *sect)
{
	if ((symbol->n_type & N_TYPE) == N_ABS)
		print_local_or_ext_64(symbol, 'A');
	else if ((symbol->n_type & N_TYPE) == N_INDR)
		print_local_or_ext_64(symbol, 'I');
	else if ((symbol->n_type & N_TYPE) & N_SECT)
		print_local_or_ext_64(symbol, match_sect_name_with_type(
								sect->segname, sect->sectname));
	else
		ft_putstr("TYPE ERROR");
}

void	print_defined_symbol_type_32(struct nlist *symbol,
													struct section *sect)
{
	if ((symbol->n_type & N_TYPE) == N_ABS)
		print_local_or_ext_32(symbol, 'A');
	else if ((symbol->n_type & N_TYPE) == N_INDR)
		print_local_or_ext_32(symbol, 'I');
	else if ((symbol->n_type & N_TYPE) & N_SECT)
		print_local_or_ext_32(symbol, match_sect_name_with_type(
								sect->segname, sect->sectname));
	else
		ft_putstr("TYPE ERROR");
}

void	print_symbol_64(t_symbol *symb, char *stringtable, t_flags *options)
{
	struct nlist_64			*symbol;
	struct section			*sect;
	struct segment_command	*seg;

	symbol = (struct nlist_64*)symb->symbol;
	sect = (struct section*)symb->sect;
	seg = (struct segment_command*)symb->seg;
	if (symbol->n_type & N_STAB)
		return ;
	if ((symbol->n_type & N_TYPE) == N_UNDF && !options->u)
	{
		print_n_char(' ', 17);
		print_local_or_ext_64(symb->symbol, 'U');
		ft_putstr(" ");
	}
	else if ((symbol->n_type & N_TYPE) != N_UNDF)
	{
		print_hexa_n(symbol->n_value, 16);
		ft_putstr(" ");
		print_defined_symbol_type_64(symbol, sect);
		ft_putstr(" ");
	}
	if (symbol->n_un.n_strx)
		ft_putstr(&(stringtable[symbol->n_un.n_strx]));
	ft_putstr("\n");
}

void	print_symbol_32(t_symbol *symb, char *stringtable, t_flags *options)
{
	struct nlist			*symbol;
	struct section			*sect;
	struct segment_command	*seg;

	symbol = (struct nlist*)symb->symbol;
	sect = (struct section*)symb->sect;
	seg = (struct segment_command*)symb->seg;
	if (symbol->n_type & N_STAB)
		return ;
	if ((symbol->n_type & N_TYPE) == N_UNDF && !options->u)
	{
		print_n_char(' ', 9);
		print_local_or_ext_32(symb->symbol, 'U');
		ft_putstr(" ");
	}
	else if ((symbol->n_type & N_TYPE) != N_UNDF)
	{
		print_hexa_n(symbol->n_value, 8);
		ft_putstr(" ");
		print_defined_symbol_type_32(symbol, sect);
		ft_putstr(" ");
	}
	if (symbol->n_un.n_strx)
		ft_putstr(&(stringtable[symbol->n_un.n_strx]));
	ft_putstr("\n");
}
