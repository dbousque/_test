

#include "malloc.h"

void	print_debug_free_null(void)
{
	char	*tmp;

	tmp = "Could not free, null pointer.\n";
	write(1, tmp, ft_strlen(tmp));
}

void	print_debug_free_raw(void *ptr, size_t size)
{
	char	*tmp;

	tmp = "Freeing large block at ";
	write(1, tmp, ft_strlen(tmp));
	print_address(ptr);
	tmp = " of size ";
	write(1, tmp, ft_strlen(tmp));
	print_number(size);
	write(1, "\n", 1);
}

void	print_debug_free_small(t_malloc_data *data, void *ptr, size_t size)
{
	char	*tmp;

	if (data->debug_print)
	{
		tmp = "Freeing small block at ";
		write(1, tmp, ft_strlen(tmp));
		print_address(ptr);
		tmp = " of size ";
		write(1, tmp, ft_strlen(tmp));
		print_number(size);
		write(1, "\n", 1);
	}
}

void	print_debug_free_tiny(t_malloc_data *data, void *ptr, size_t size)
{
	char	*tmp;

	if (data->debug_print)
	{
		tmp = "Freeing tiny block at ";
		write(1, tmp, ft_strlen(tmp));
		print_address(ptr);
		tmp = " of size ";
		write(1, tmp, ft_strlen(tmp));
		print_number(size);
		write(1, "\n", 1);
	}
}

void	print_debug_realloc_raw(void *ptr, size_t start_size, size_t end_size)
{
	char	*tmp;

	tmp = "Reallocing large block at ";
	write(1, tmp, ft_strlen(tmp));
	print_address(ptr);
	tmp = " of size ";
	write(1, tmp, ft_strlen(tmp));
	print_number(start_size);
	tmp = " to size ";
	write(1, tmp, ft_strlen(tmp));
	print_number(end_size);
	write(1, "\n", 1);
}