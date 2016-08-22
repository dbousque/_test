

#include "otool.h"

struct section_64	*n_sect_in_seg_64(struct segment_command_64 *seg, size_t n)
{
	void		*sect;
	size_t		i;

	sect = ((void*)seg) + sizeof(struct segment_command_64);
	i = 0;
	while (n > 0 && i < n - 1)
	{
		sect += sizeof(struct section_64);
		i++;
	}
	return (sect);
}

struct section_64	*get_n_sect_64(void *ptr, size_t n,
												struct segment_command_64 **seg)
{
	uint32_t				i;
	int						nb_sect;
	struct load_command		*lc;

	lc = (struct load_command*)(ptr + sizeof(struct mach_header_64));
	nb_sect = 0;
	i = 0;
	while (i < ((struct mach_header_64*)ptr)->ncmds)
	{
		if (!valid_pointer(((void*)lc) + sizeof(struct load_command)))
			return (NULL);
		if (lc->cmd == LC_SEGMENT_64)
		{
			if (nb_sect + ((struct segment_command_64*)lc)->nsects >= n)
			{
				*seg = (struct segment_command_64*)lc;
				return (n_sect_in_seg_64((struct segment_command_64*)lc,
															n - nb_sect));
			}
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
	while (n > 0 && i < n - 1)
	{
		sect += sizeof(struct section);
		i++;
	}
	return (sect);
}

struct section	*get_n_sect_32(void *ptr, size_t n,
												struct segment_command **seg)
{
	uint32_t				i;
	int						nb_sect;
	struct load_command		*lc;

	lc = (struct load_command*)(ptr + sizeof(struct mach_header));
	nb_sect = 0;
	i = 0;
	while (i < ((struct mach_header*)ptr)->ncmds)
	{
		if (!valid_pointer(((void*)lc) + sizeof(struct load_command)))
			return (NULL);
		if (lc->cmd == LC_SEGMENT)
		{
			if (nb_sect + ((struct segment_command*)lc)->nsects >= n)
			{
				*seg = (struct segment_command*)lc;
				return (n_sect_in_seg_32((struct segment_command*)lc, n - nb_sect));
			}
			nb_sect += ((struct segment_command*)lc)->nsects;
		}
		i++;
		lc = ((void*)lc) + lc->cmdsize;
	}
	return (NULL);
}