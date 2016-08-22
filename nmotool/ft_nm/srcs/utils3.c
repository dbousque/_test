

#include "nm.h"

void	print_n_char(char c, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
}

void	ft_putstrn(char *str, int n)
{
	write(1, str, n);
}