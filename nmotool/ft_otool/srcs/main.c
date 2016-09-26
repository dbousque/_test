/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 14:42:44 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:33:01 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

char	get_file(char *filename, char **ptr, size_t *size, int *fd)
{
	struct stat	buf;

	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
	{
		print_error_file("open failed", filename);
		return (0);
	}
	if (fstat(*fd, &buf) < 0)
	{
		print_error_file("fstat failed", filename);
		close(*fd);
		return (0);
	}
	*size = buf.st_size;
	if ((*ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, *fd, 0))
				== MAP_FAILED)
	{
		print_error_file("mmap failed", filename);
		close(*fd);
		return (0);
	}
	return (1);
}

void	launch_otool_for_file(char *filename)
{
	char	*ptr;
	size_t	size;
	int		fd;

	fd = 0;
	if (!(get_file(filename, &ptr, &size, &fd)))
		return ;
	otool(ptr, size, filename, 1);
	if (munmap(ptr, size) < 0)
		print_error_file("munmap failed", filename);
	close(fd);
}

int		display_help(void)
{
	char	*t;

	t = "             -- otool --\n    displays content of Mach O files\n\n";
	ft_putstr(t);
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
