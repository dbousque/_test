

#include "ft_printf.h"

void	ft_putoctal(long value)
{
	char	*res;

	if ((res = ft_ntoa_base(value, "01234567")))
		ft_putstr(res);
}
