

#include <stdlib.h>

int		main(void)
{
	int		i;
	void	*ptr;

	i = 0;
	ptr = 12;
	while (i < 100)
	{
		free(ptr);
		ptr = malloc(100);
		free(ptr);
		free(ptr);
		free(NULL);
		free(NULL - 1);
		ptr = malloc(8);
		//ptr = realloc(ptr, 5000);
		i++;
	}
	free(ptr);
}