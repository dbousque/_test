

#include "ft_printf.h"

void		get_precision(const char *format, t_format *format_var, int *i, va_list ap)
{
	int		res;

	if (format[*i] == '.' && format[*i + 1] >= '0' && format[*i + 1] <= '9')
	{
		res = ft_atoi(format + *i + 1);
		*i += ft_intlen(res) + 1;
		format_var->precision = res;
	}
	else if (format[*i] == '.' && format[*i + 1] == '*')
	{
		(*i) += 2;
		format_var->precision = va_arg(ap, int);

	}
	else if (format[*i] == '.')
	{
		(*i)++;
		format_var->precision = 0;
	}
	else
		format_var->precision = -1;
}
