

#include "ft_printf.h"

int		ft_putaddr(void *addr, char long_long)
{
	long long	value;
	char		*res;

	value = (long_long ? (long long)addr : (long)addr);
	res = ft_ntoa_base(value, "0123456789abcdef");
	ft_putstr("0x");
	if (res)
		ft_putstr(res);
	else
		ft_putstr("0");
	return ((res ? ft_strlen(res) : 1) + 2);
}

int		ft_putaddr_un(void *addr, char long_long)
{
	unsigned long long	value;
	char				*res;

	value = (long_long ? (unsigned long long)addr : (unsigned long)addr);
	res = ft_ntoa_base_un(value, "0123456789abcdef");
	ft_putstr("0x");
	if (res)
		ft_putstr(res);
	else
		ft_putstr("0");
	return ((res ? ft_strlen(res) : 1) + 2);
}
