

#include "ft_printf.h"

int		ft_putoctal(long long value)
{
	char	*res;

	if ((res = ft_ntoa_base(value, "01234567")))
	{
		ft_putstr(res);
		return (ft_strlen(res));
	}
	return (0);
}

int		ft_putoctal_un(unsigned long long value)
{
	char	*res;

	if ((res = ft_ntoa_base_un(value, "01234567")))
	{
		ft_putstr(res);
		return (ft_strlen(res));
	}
	return (0);
}
