

#include "nm.h"


	#  include <stdio.h>

void	bad_executable(void)
{
	print_error("Unrecognized executable file format");
}

void	*bad_executable_null(void)
{
	bad_executable();
	return (NULL);
}

void	print_local_or_ext(struct nlist_64 *symbol, char c)
{
	char	to_print;

	to_print = c;
	if (c >= 'A' && c <= 'Z' && !symbol->n_type & N_EXT)
		to_print = c - 'A' + 'a';
	write(1, &to_print, 1);
}

struct section_64	*n_sect_in_seg_64(struct segment_command_64 *seg, size_t n)
{
	void		*sect;
	size_t		i;

	sect = ((void*)seg) + sizeof(struct segment_command_64);
	i = 0;
	while (i < n - 1)
	{
		sect += sizeof(struct section_64);
		i++;
	}
	return (sect);
}

struct section_64	*get_n_sect_64_bis(struct load_command *lc, void *end_file,
														int ncmds, size_t n)
{
	int		i;
	int		nb_sect;

	nb_sect = 0;
	i = 0;
	while (i < ncmds)
	{
		if (((void*)lc) + sizeof(struct load_command) > end_file)
			return (bad_executable_null());
		if (lc->cmd == LC_SEGMENT_64)
		{
			if (nb_sect + ((struct segment_command_64*)lc)->nsects >= n)
				return (n_sect_in_seg_64((struct segment_command_64*)lc,
															n - nb_sect));
			nb_sect += ((struct segment_command_64*)lc)->nsects;
		}
		i++;
		lc = ((void*)lc) + lc->cmdsize;
	}
	return (NULL);
}

struct section	*n_sect_in_seg_32(struct segment_command *seg, size_t n)
{
	void		*sect;
	size_t		i;

	sect = ((void*)seg) + sizeof(struct segment_command);
	i = 0;
	while (i < n - 1)
	{
		sect += sizeof(struct section);
		i++;
	}
	return (sect);
}

struct section	*get_n_sect_32_bis(struct load_command *lc, void *end_file,
														int ncmds, size_t n)
{
	int		i;
	int		nb_sect;

	nb_sect = 0;
	i = 0;
	while (i < ncmds)
	{
		if (((void*)lc) + sizeof(struct load_command) > end_file)
			return (bad_executable_null());
		if (lc->cmd == LC_SEGMENT)
		{
			if (nb_sect + ((struct segment_command*)lc)->nsects >= n)
				return (n_sect_in_seg_32((struct segment_command*)lc, n - nb_sect));
			nb_sect += ((struct segment_command*)lc)->nsects;
		}
		i++;
		lc = ((void*)lc) + lc->cmdsize;
	}
	return (NULL);
}

struct section_64	*get_n_sect_64(char *ptr, size_t file_size, size_t n)
{
	struct mach_header_64	*header;

	header = (struct mach_header_64*)ptr;
	return (get_n_sect_64_bis((void*)ptr + sizeof(struct mach_header_64),
								(void*)ptr + file_size, header->ncmds, n));
}

struct section	*get_n_sect_32(char *ptr, size_t file_size, size_t n)
{
	struct mach_header	*header;

	header = (struct mach_header*)ptr;
	return (get_n_sect_32_bis((void*)ptr + sizeof(struct mach_header),
								(void*)ptr + file_size, header->ncmds, n));
}

char	ft_streq(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (!str1[i] && !str2[i])
		return (1);
	return (0);
}

char	match_sect_name_with_type(char *name)
{
	if (ft_streq(name, SECT_TEXT))
		return ('T');
	if (ft_streq(name, SECT_DATA))
		return ('D');
	if (ft_streq(name, SECT_BSS))
		return ('B');
	if (ft_streq(name, SECT_COMMON))
		return ('C');
	return ('S');
}

char	get_type_of_n_sect_64(void *ptr, size_t file_size, size_t n)
{
	struct section_64	*sect;
	char				*name;

	sect = get_n_sect_64(ptr, file_size, n);
	if (!sect)
		return ('!');
	if (((void*)sect) + sizeof(struct section_64) > ptr + file_size)
	{
		bad_executable();
		return ('!');
	}
	name = sect->sectname;
	return (match_sect_name_with_type(name));
}

char	get_type_of_n_sect_32(void *ptr, size_t file_size, size_t n)
{
	struct section	*sect;
	char			*name;

	sect = get_n_sect_32(ptr, file_size, n);
	if (!sect)
		return ('!');
	if (((void*)sect) + sizeof(struct section_64) > ptr + file_size)
	{
		bad_executable();
		return ('!');
	}
	name = sect->sectname;
	return (match_sect_name_with_type(name));
}

void	read_symtab_command(struct symtab_command *sym, void *ptr,
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
		if ((symbol->n_type & N_TYPE) == N_UNDF)
			print_local_or_ext(symbol, 'U');
		else if ((symbol->n_type & N_TYPE) == N_ABS)
			print_local_or_ext(symbol, 'A');
		else if ((symbol->n_type & N_TYPE) == N_INDR)
			print_local_or_ext(symbol, 'I');
		else if ((symbol->n_type & N_TYPE) & N_SECT)
			print_local_or_ext(symbol, get_type_of_n_sect_64(ptr,
					file_size, symbol->n_sect));
		else
			ft_putstr("TYPE ERROR");
		ft_putstr(" ");
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