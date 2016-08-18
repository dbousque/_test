

#include "nm.h"

void	print_symbols(t_list *symbols, char *stringtable)
{
	int		i;

	i = 0;
	while (i < symbols->len)
	{
		if (((t_symbol*)symbols->elts[i])->exec_type == BITS_64)
			print_symbol_64(symbols->elts[i], stringtable);
		else if (((t_symbol*)symbols->elts[i])->exec_type == BITS_32)
			print_symbol_32(symbols->elts[i], stringtable);
		i++;
	}
}

void	handle_file(char *ptr, char type)
{
	t_list	*symbols;
	char	*stringtable;

	stringtable = NULL;
	symbols = NULL;
	if (type == MACH_O_64)
		symbols = get_mach_o_64_symbols(ptr, &stringtable);
	else if (type == MACH_O_32)
		symbols = get_mach_o_32_symbols(ptr, &stringtable);
	else if (type == FAT)
		symbols = get_fat_symbols(ptr, &stringtable);
	if (symbols)
		print_symbols(symbols, stringtable);
}