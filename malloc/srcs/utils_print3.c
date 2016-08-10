

#include "malloc.h"

void	print_debug_bad_free(void *ptr)
{
	char	*tmp;

	tmp = "Free called on unallocated pointer : ";
	write(1, tmp, ft_strlen(tmp));
	print_address(ptr);
	write(1, "\n", 1);
}