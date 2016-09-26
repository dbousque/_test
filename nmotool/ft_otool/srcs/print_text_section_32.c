/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_text_section_32.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:36:21 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:36:23 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	print_section_32(void *ptr, size_t offset, size_t size, char *file_name)
{
	long		decal;
	size_t		i;
	uint32_t	filetype;

	filetype = get_filetype();
	if (filetype == MH_OBJECT)
		decal = -((long)offset);
	else if (filetype == MH_DYLIB || filetype == MH_BINDATLOAD)
		decal = 0;
	else
		decal = 0x1000;
	(void)ptr;
	(void)size;
	(void)file_name;
	ft_putstr("(__TEXT,__text) section\n");
	i = 0;
	while (i < size)
	{
		print_hexa_n(decal + offset + i, 8);
		ft_putstr(" ");
		print_n_bytes(ptr, offset + i, 16, offset + size);
		ft_putstr("\n");
		i += 16;
	}
}

void	print_text_32(void *ptr, struct segment_command *seg,
										t_flags *options, char *file_name)
{
	uint32_t		i;
	struct section	*sect;

	(void)options;
	i = 0;
	sect = (void*)seg + sizeof(struct segment_command);
	while (i < seg->nsects)
	{
		if (!valid_pointer((void*)sect + sizeof(struct section)))
			return ;
		if (ft_streq(sect->sectname, SECT_TEXT))
		{
			if (!valid_pointer(ptr + sect->offset))
				return ;
			if (!valid_pointer(ptr + sect->offset + sect->size - 1))
				return ;
			print_section_32(ptr, sect->offset, sect->size, file_name);
			return ;
		}
		i++;
		sect = (void*)sect + sizeof(struct section);
	}
}

void	print_text_section_32(void *ptr, t_flags *options, char *file_name)
{
	int						ncmds;
	int						i;
	struct mach_header		*header;
	struct load_command		*lc;

	header = (struct mach_header*)ptr;
	set_filetype(header->filetype);
	ncmds = header->ncmds;
	lc = ptr + sizeof(struct mach_header);
	i = 0;
	while (i < ncmds)
	{
		if (!valid_pointer(((void*)lc) + sizeof(struct load_command)))
			return ;
		if (lc->cmd == LC_SEGMENT
			&& (ft_streq(((struct segment_command*)lc)->segname, SEG_TEXT)
				|| header->filetype == MH_OBJECT))
			print_text_32(ptr, (struct segment_command*)lc, options, file_name);
		i++;
		lc = ((void*)lc) + lc->cmdsize;
	}
}
