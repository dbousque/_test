

#include "ft_printf.h"

void	ft_putoctal(long long value)
{
	char	*res;

	if ((res = ft_ntoa_base(value, "01234567")))
		ft_putstr(res);
}

void	ft_putoctal_un(unsigned long long value)
{
	char	*res;

	if ((res = ft_ntoa_base_un(value, "01234567")))
		ft_putstr(res);
}
