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

#include "nm.h"

void	nm(char *ptr, size_t size)
{
	unsigned int	magic;

	set_valid_pointer(ptr, ptr + size);
	magic = *(int*)ptr;
	if (magic == MH_MAGIC_64
				&& valid_pointer(ptr + sizeof(struct mach_header_64)))
		handle_file(ptr, MACH_O_64);
	else if (magic == MH_MAGIC
				&& valid_pointer(ptr + sizeof(struct mach_header)))
		handle_file(ptr, MACH_O_32);
	else if (magic == FAT_MAGIC
				&& valid_pointer(ptr + sizeof(struct fat_header)))
		handle_file(ptr, FAT);
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
	free_all();
	return (0);
}
