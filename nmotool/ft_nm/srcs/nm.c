

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

int 	cmp_by_numeric(void *elt1, void *elt2)
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

int 	cmp_by_name(void *elt1, void *elt2)
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
		quicksort(symbols->elts, 0, symbols->len, cmp_by_numeric);
	if (!options->p && !options->n)
		quicksort(symbols->elts, 0, symbols->len, cmp_by_name);
	if (!options->p && options->r)
		reverse_list(symbols);
}

char	*handle_stringtable(char *ptr, char option)
{
	static char		*str = NULL;

	if (option == 1)
		str = ptr;
	return (str);
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
	t_list	*symbols;
	char	*stringtable;
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