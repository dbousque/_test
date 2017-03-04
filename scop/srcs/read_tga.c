

#include "myopengl.h"

char	*read_tga(char *path, int *width, int *height)
{
	char	*contents;

	contents = read_file(path, 20 * 1024 * 1024);
	if (!contents)
		return (NULL);
	*width = *((short*)(contents + 12));
	*height = *((short*)(contents + 14));
	return (contents + 18);
}