

#include "malloc.h"

void	*my_calloc(t_malloc_data *data, size_t size)
{
	unsigned char	*res;
	size_t			i;

	res = my_malloc(data, size);
	i = 0;
	while (i < size)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}

void	*my_reallocf(t_malloc_data *data, void *ptr, size_t size)
{
	void	*res;
	char	invalid_pointer;

	res = my_realloc(data, ptr, size, &invalid_pointer);
	if (!res && !invalid_pointer)
		my_free(data, ptr);
	return (res);
}