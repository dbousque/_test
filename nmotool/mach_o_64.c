

#include "nm.h"

t_symbol	*build_symb_from_symbol_64(struct nlist_64 *symbol, void *ptr)
{
	t_symbol					*symb;
	struct section_64			*sect;
	struct segment_command_64	*seg;

	symb = my_malloc(sizeof(t_symbol));
	symb->exec_type = BITS_64;
	symb->symbol = symbol;
	if ((symbol->n_type & N_TYPE) & N_SECT)
	{
		sect = get_n_sect_64(ptr, symbol->n_sect, &seg);
		symb->seg = seg;
		symb->sect = sect;
	}
	return (symb);
}

t_list	*read_symtab_command_64(struct symtab_command *sym, void *ptr,
														char **stringtable)
{
	uint32_t		i;
	struct nlist_64	*symbol;
	t_symbol		*to_store_symb;
	t_list			*symbols;

	symbols = new_list();
	*stringtable = ((void*)ptr) + sym->stroff;
	symbol = ((void*)ptr) + sym->symoff;
	i = 0;
	while (i < sym->nsyms)
	{
		if (!valid_pointer(((void*)symbol) + sizeof(struct nlist_64)))
			return (NULL);
		if (!valid_pointer((void*)(*stringtable + symbol->n_un.n_strx)))
			return (NULL);
		to_store_symb = build_symb_from_symbol_64(symbol, ptr);
		add_to_list(symbols, to_store_symb);
		symbol = ((void*)symbol) + sizeof(struct nlist_64);
		i++;
	}
	return (symbols);
}

t_list	*get_mach_o_64_symbols(void *ptr, char **stringtable)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;

	header = (struct mach_header_64*)ptr;
	ncmds = header->ncmds;
	lc = ptr + sizeof(struct mach_header_64);
	i = 0;
	while (i < ncmds)
	{
		if (!valid_pointer(((void*)lc) + sizeof(struct load_command)))
			return (NULL);
		if (lc->cmd == LC_SYMTAB)
			return (read_symtab_command_64((struct symtab_command*)lc,
														ptr, stringtable));
		i++;
		lc = ((void*)lc) + lc->cmdsize;
	}
	return (NULL);
}