

#include "ft_printf.h"

int		ft_putbinary(long long value, char **str)
{
	if ((*str = ft_ntoa_base_un(value, "01")))
		return (ft_strlen(*str));
	return (0);
}
