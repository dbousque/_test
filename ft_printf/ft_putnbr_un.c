

#include "ft_printf.h"

int		ft_putnbr_un(unsigned int n)
{
	int		length;

	if (n < 10)
	{
		ft_putchar(n + '0');
		return (1);
	}
	else
	{
		length = ft_putnbr_un(n / 10);
		ft_putchar(n % 10 + '0');
		return (length + 1);
	}
}
