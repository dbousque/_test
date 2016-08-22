

#include "otool.h"

static void	print_n_bytes(unsigned char *start, size_t i, int nb_bytes,
																	size_t end)
{
	size_t	x;

	(void)end;
	x = i;
	while (x < i + nb_bytes && x < end)
	{
		print_hexa_n(start[x], 2);
		ft_putstr(" ");
		x++;
	}
}

void	print_section_64(void *ptr, size_t offset, size_t size, char *file_name)
{
	size_t	decal;
	size_t	i;

	decal = 0x100000000;
	(void)ptr;
	(void)size;
	(void)file_name;
	ft_putstr("(__TEXT,__text) section\n");
	i = 0;
	while (i < size)
	{
		print_hexa_n(decal + offset + i, 16);
		ft_putstr(" ");
		print_n_bytes(ptr, offset + i, 16, offset + size);
		ft_putstr("\n");
		i += 16;
	}
}

void	print_text_64(void *ptr, struct segment_command_64 *seg,
										t_flags *options, char *file_name)
{
	uint32_t			i;
	struct section_64	*sect;

	(void)options;
	i = 0;
	sect = (void*)seg + sizeof(struct segment_command_64);
	while (i < seg->nsects)
	{
		if (!valid_pointer((void*)sect + sizeof(struct section_64)))
			return ;
		if (ft_streq(sect->sectname, SECT_TEXT))
		{
			if (!valid_pointer(ptr + sect->offset))
				return ;
			if (!valid_pointer(ptr + sect->offset + sect->size - 1))
				return ;
			print_section_64(ptr, sect->offset, sect->size, file_name);
			return ;
		}
		i++;
		sect = (void*)sect + sizeof(struct section_64);
	}
}

void	print_text_section_64(void *ptr, t_flags *options, char *file_name)
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
			return ;
		if (lc->cmd == LC_SEGMENT_64
			&& ft_streq(((struct segment_command_64*)lc)->segname, SEG_TEXT))
			print_text_64(ptr, (struct segment_command_64*)lc, options, file_name);
		i++;
		lc = ((void*)lc) + lc->cmdsize;
	}
}