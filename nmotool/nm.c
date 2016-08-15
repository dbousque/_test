

#include "nm.h"

void	bad_executable(void)
{
	print_error("Unrecognized executable file format");
}

void	read_symtab_command(struct symtab_command *sym, char *ptr,
														size_t file_size)
{
	char			*stringtable;
	uint32_t		i;
	struct nlist_64	*symbol;
	//t_list			*to_print;

	//to_print = new_list();
	stringtable = ((void*)ptr) + sym->stroff;
	symbol = ((void*)ptr) + sym->symoff;
	i = 0;
	while (i < sym->nsyms)
	{
		if (((void*)symbol) + sizeof(struct nlist_64) > (void*)ptr + file_size)
			return (bad_executable());
		if (((void*)(stringtable + symbol->n_un.n_strx)) >= (void*)ptr + file_size)
			return (bad_executable());
		if (symbol->n_value)
		{
			print_hexa_n(symbol->n_value, 16);
			ft_putstr(" ");
		}
		else
			print_n_char(' ', 17);
		if (symbol->n_un.n_strx)
			ft_putstr(&(stringtable[symbol->n_un.n_strx]));
		ft_putstr("\n");
		symbol = ((void*)symbol) + sizeof(struct nlist_64);
		i++;
	}
}

void	handle_64(char *ptr, size_t file_size)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;

	header = (struct mach_header_64*)ptr;
	ncmds = header->ncmds;
	lc = ((void*)ptr) + sizeof(struct mach_header_64);
	i = 0;
	while (i < ncmds)
	{
		if (((void*)lc) + sizeof(struct load_command) > (void*)ptr + file_size)
			return (bad_executable());
		if (lc->cmd == LC_SYMTAB)
		{
			read_symtab_command((struct symtab_command*)lc, ptr, file_size);
			return ;
		}
		i++;
		lc = ((void*)lc) + lc->cmdsize;
	}
}

void	nm(char *ptr, size_t size)
{
	unsigned int	magic;

	magic = *(int*)ptr;
	if (magic == MH_MAGIC_64 && size >= sizeof(struct mach_header_64))
		handle_64(ptr, size);
	else if (1)
		handle_64(ptr, size);
	else
		return (bad_executable());
}

char	get_file(char *filename, char **ptr, size_t *size)
{
	int			fd;
	struct stat	buf;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error_file("open failed", filename);
		return (0);
	}
	if (fstat(fd, &buf) < 0)
	{
		print_error_file("fstat failed", filename);
		return (0);
	}
	*size = buf.st_size;
	if ((*ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		print_error_file("mmap failed", filename);
		return (0);
	}
	return (1);
}

void	launch_nm_for_file(char *filename)
{
	char	*ptr;
	size_t	size;

	if (!(get_file(filename, &ptr, &size)))
		return ;
	nm(ptr, size);
	if (munmap(ptr, size) < 0)
		print_error_file("munmap failed", filename);
}

int		main(int argc, char **argv)
{
	int		i;

	if (argc < 2)
		launch_nm_for_file("a.out");
	i = 1;
	while (i < argc)
	{
		if (argc > 2)
		{
			ft_putstr("\n");
			ft_putstr(argv[i]);
			ft_putstr(":\n");
		}
		launch_nm_for_file(argv[i]);
		i++;
	}
	return (0);
}