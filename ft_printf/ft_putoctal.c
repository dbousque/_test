

#include "ft_printf.h"

int		ft_putoctal(long long value, char **str)
{
	if ((*str = ft_ntoa_base(value, "01234567")))
		return (ft_strlen(*str));
	return (0);
}

int		ft_putoctal_un(unsigned long long value, char **str)
{
	if ((*str = ft_ntoa_base_un(value, "01234567")))
		return (ft_strlen(*str));
	return (0);
}
