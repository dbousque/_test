

#include "includes/libfts.h"
#include <fcntl.h>
#include <unistd.h>

int		main(void)
{
	int	fd = open("/Users/dodo/projects/root-me-app-system/.passwd", O_RDONLY);
	ft_cat(fd);
	return (0);
}
