/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:08:14 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:19:18 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	maybe_launch_64(t_symbol *symbol, char *stringtable, char *file_name,
															t_flags *options)
{
	if (options->u
		&& !((((struct nlist_64*)symbol->symbol)->n_type & N_TYPE) == N_UNDF))
		return ;
	if (options->u_maj
		&& (((struct nlist_64*)symbol->symbol)->n_type & N_TYPE) == N_UNDF)
		return ;
	if (!options->g || ((struct nlist_64*)symbol->symbol)->n_type & N_EXT)
	{
		if (options->o)
		{
			ft_putstr(file_name);
			ft_putstr(": ");
		}
		print_symbol_64(symbol, stringtable, options);
	}
}

void	maybe_launch_32(t_symbol *symbol, char *stringtable, char *file_name,
															t_flags *options)
{
	if (options->u
		&& !((((struct nlist*)symbol->symbol)->n_type & N_TYPE) == N_UNDF))
		return ;
	if (options->u_maj
		&& (((struct nlist*)symbol->symbol)->n_type & N_TYPE) == N_UNDF)
		return ;
	if (!options->g || ((struct nlist*)symbol->symbol)->n_type & N_EXT)
	{
		if (options->o)
		{
			ft_putstr(file_name);
			ft_putstr(": ");
		}
		print_symbol_32(symbol, stringtable, options);
	}
}

char	*get_stringtable(void)
{
	return (handle_stringtable(NULL, 2));
}

void	set_stringtable(char *ptr)
{
	handle_stringtable(ptr, 1);
}

void	handle_file(char *ptr, char type, char *file_name)
{
	t_list		*symbols;
	char		*stringtable;
	t_flags		*options;

	stringtable = NULL;
	symbols = NULL;
	options = (t_flags*)get_current_options();
	if (type == MACH_O_64)
		symbols = get_mach_o_64_symbols(ptr, &stringtable);
	else if (type == MACH_O_32)
		symbols = get_mach_o_32_symbols(ptr, &stringtable);
	set_stringtable(stringtable);
	if (symbols)
	{
		sort_symbols(symbols, options);
		print_symbols(symbols, stringtable, options, file_name);
	}
}
