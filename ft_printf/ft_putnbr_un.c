

#include "ft_printf.h"

void	ft_putnbr_un(unsigned int n)
{
	if (n < 10)
		ft_putchar(n + '0');
	else
	{
		ft_putnbr_un(n / 10);
		ft_putchar(n % 10 + '0');
	}
}
