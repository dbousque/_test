

#include "my_malloc.h"


	# include <stdio.h>

int		main(void)
{
	size_t	i;
	char	*lol;

	i = 0;
	while (i < 4096000)
	{
		lol = my_malloc(567);
		lol[1] = 42;
		i++;
	}
	my_malloc(20);
	my_malloc(15);
	printf("BEFORE FREE\n");
	fflush(stdout);
	free_all();
	return (0);
}