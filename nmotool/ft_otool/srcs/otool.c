/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:27:34 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:35:39 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	handle_fat(void *ptr, size_t size, char *file_name)
{
	void	*start;
	size_t	res_size;

	start = get_fat_start(ptr, &res_size, size);
	if (!start)
	{
		bad_executable();
		return ;
	}
	otool(start, res_size, file_name, 0);
}

void	print_file_name(char *file_name, unsigned int magic, char *ptr,
																	size_t size)
{
	(void)magic;
	if (size >= 8 && ptr[0] == '!' && ptr[1] == '<' && ptr[2] == 'a'
		&& ptr[3] == 'r' && ptr[4] == 'c' && ptr[5] == 'h'
		&& ptr[6] == '>' && ptr[7] == '\n')
	{
		ft_putstr("Archive : ");
		ft_putstr(file_name);
		ft_putstr("\n");
	}
	else
	{
		ft_putstr(file_name);
		ft_putstr(":\n");
	}
}

void	handle_file(char *ptr, char type, char *file_name)
{
	t_flags		*options;

	options = (t_flags*)get_current_options();
	if (type == MACH_O_64)
		print_text_section_64(ptr, options, file_name);
	else if (type == MACH_O_32)
		print_text_section_32(ptr, options, file_name);
}

char	is_ranlib(char *ptr)
{
	if (ptr[0] == '!' && ptr[1] == '<' && ptr[2] == 'a'
		&& ptr[3] == 'r' && ptr[4] == 'c' && ptr[5] == 'h'
		&& ptr[6] == '>' && ptr[7] == '\n')
		return (1);
	return (0);
}

void	otool(char *ptr, size_t size, char *file_name, char print_file)
{
	unsigned int	magic;

	magic = *(int*)ptr;
	if (print_file)
		print_file_name(file_name, magic, ptr, size);
	if (magic == FAT_CIGAM && ptr + sizeof(struct fat_header) < ptr + size)
	{
		handle_fat(ptr, size, file_name);
		return ;
	}
	else if (size >= 8 && is_ranlib(ptr))
	{
		handle_ranlib(ptr + 8, size, file_name);
		return ;
	}
	set_valid_pointer(ptr, ptr + size);
	if (magic == MH_MAGIC_64
				&& valid_pointer(ptr + sizeof(struct mach_header_64)))
		handle_file(ptr, MACH_O_64, file_name);
	else if (magic == MH_MAGIC
				&& valid_pointer(ptr + sizeof(struct mach_header)))
		handle_file(ptr, MACH_O_32, file_name);
	else
		bad_executable();
	reset_valid_pointer();
}
