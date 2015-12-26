

#include "ft_printf.h"

int		ft_putaddr(void *addr, char long_long, char **str, t_format *format)
{
	long long	value;

	value = (long_long ? (long long)addr : (long)addr);
	format->u_value = value;
	*str = ft_ntoa_base(value, "0123456789abcdef");
	if (!(*str))
		*str = ft_strdup("0");
	return (ft_strlen(*str));
}

/*int		ft_putaddr_un(void *addr, char long_long, char **str, t_format *format)
{
	unsigned long long	value;

	value = (long_long ? (unsigned long long)addr : (unsigned long)addr);
	format->u_value = value;
	*str = ft_ntoa_base_un(value, "0123456789abcdef");
	if (!(*str))
		*str = ft_strdup("0");
	return (ft_strlen(*str));
}*/
