

#include "ft_printf.h"

void			ft_putaddr(void *addr)
{
	long long	value;
	char		*res;

	value = (long long)addr;
	res = ft_ntoa_base(value, "0123456789abcdef");
	if (res)
	{
		ft_putstr("0x");
		ft_putstr(res);
	}
}

void			ft_putaddr_un(void *addr)
{
	unsigned long long	value;
	char				*res;

	value = (unsigned long long)addr;
	res = ft_ntoa_base_un(value, "0123456789abcdef");
	if (res)
	{
		ft_putstr("0x");
		ft_putstr(res);
	}
}
