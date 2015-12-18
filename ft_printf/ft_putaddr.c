

#include "ft_printf.h"

void			ft_putaddr(void *addr)
{
	long	value;
	char	*res;

	value = (long)addr;
	res = ft_ntoa_base(value, "0123456789abcdef");
	if (res)
	{
		ft_putstr("0x");
		ft_putstr(res);
	}
}
