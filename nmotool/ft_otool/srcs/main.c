/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 14:42:44 by dbousque          #+#    #+#             */
/*   Updated: 2016/08/18 14:42:46 by dbousque         ###   ########.fr       */
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

void	otool(char *ptr, size_t size, char *file_name, char print_file)
{
	unsigned int	magic;

	magic = *(int*)ptr;
	if (print_file)
		print_file_name(file_name, magic, ptr, size);
	if (magic == FAT_CIGAM
				&& ptr + sizeof(struct fat_header) < ptr + size)
	{
		handle_fat(ptr, size, file_name);
		return ;
	}
	else if (size >= 8 && ptr[0] == '!' && ptr[1] == '<' && ptr[2] == 'a'
		&& ptr[3] == 'r' && ptr[4] == 'c' && ptr[5] == 'h' && ptr[6] == '>' && ptr[7] == '\n')
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
	if ((*ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
				== MAP_FAILED)
	{
		print_error_file("mmap failed", filename);
		return (0);
	}
	return (1);
}

void	launch_otool_for_file(char *filename)
{
	char	*ptr;
	size_t	size;

	if (!(get_file(filename, &ptr, &size)))
		return ;
	otool(ptr, size, filename, 1);
	if (munmap(ptr, size) < 0)
		print_error_file("munmap failed", filename);
}

int		display_help(void)
{
	ft_putstr("             -- otool --\n    displays content of Mach O files\n\n");
	ft_putstr("implemented options :\n");
	clear_options();
	free_all();
	return (0);
}

int		main(int argc, char **argv)
{
	int		i;
	int		start;
	t_flags	options;

	if (argc > 1 && ft_streq(argv[1], "-help"))
		return (display_help());
	void_options(&options);
	set_current_options(&options);
	start = read_options(argc, argv, &options);
	i = 0;
	while (i + start < argc)
	{
		launch_otool_for_file(argv[i + start]);
		i++;
	}
	clear_options();
	free_all();
	return (0);
}
