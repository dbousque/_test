

#include <stdlib.h>

int		main(void)
{
	int		i;
	void	*ptr;

	malloc(3);


	ptr = malloc(139);

	free(ptr);
	return (0);
}