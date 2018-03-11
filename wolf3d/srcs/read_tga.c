

#include "wolf3d.h"

char	*read_tga_error(char *path, char error, int max_size)
{
	if (error == 1)
	{
		ft_putstr("Could not read file \"");
		ft_putstr(path);
		ft_putstr("\"\n");
	}
	if (error == 2)
		ft_putstr("malloc error\n");
	if (error == 3)
	{
		ft_printf("Maximum file size of %d bytes ", max_size);
		ft_printf("exceeded while reading file \"%s\"\n", path);
	}
	return (NULL);
}

char	*read_tga(char *path, int *width, int *height, int *pixel_width)
{
	char	*content;
	char	error;
	int		max_size;
	int		content_size;

	max_size = 20 * 1024 * 1024;
	content = read_whole_file(path, &error, max_size, &content_size);
	if (error == 1 || error == 2 || error == 3)
		return (read_tga_error(path, error, max_size));
	if (!content)
		return (NULL);
	*width = *((short*)(content + 12));
	*height = *((short*)(content + 14));
	content_size -= 18;
	if (*width * *height * 3 == content_size)
		*pixel_width = 3;
	else if (*width * *height * 4 == content_size)
		*pixel_width = 4;
	else
	{
		ft_printf("Invalid TGA file\n");
		return (NULL);
	}
	return (content + 18);
}