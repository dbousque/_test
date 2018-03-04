

#include "wolf3d.h"

char	*read_tga_end(char *content, int *width, int *height)
{
	if (!content)
		return (NULL);
	*width = *((short*)(content + 12));
	*height = *((short*)(content + 14));
	return (content + 18);
}

char	*read_tga(char *path, int *width, int *height)
{
	char	*content;
	char	error;
	int		max_size;

	max_size = 20 * 1024 * 1024;
	content = read_whole_file(path, &error, max_size);
	if (error == 1)
	{
		ft_putstr("Could not read file \"");
		ft_putstr(path);
		ft_putstr("\"\n");
		return (NULL);
	}
	if (error == 2)
	{
		ft_putstr("malloc error\n");
		return (NULL);
	}
	if (error == 3)
	{
		ft_printf("Maximum file size of %d bytes ", max_size);
		ft_printf("exceeded while reading file \"%s\"\n", path);
		return (NULL);
	}
	return (read_tga_end(content, width, height));
}