

#include "ft_printf.h"

int			get_size(char c)
{
	if (c == HH)
		return (sizeof(char));
	if (c == H)
		return (sizeof(short));
	if (c == L)
		return (sizeof(long));
	if (c == LL)
		return (sizeof(long long));
	if (c == Z)
		return (sizeof(size_t));
	if (c == J)
		return (sizeof(intmax_t));
	return (0);
}

void		update_length(t_format *format_var, char new_length)
{
	int		sizeof_current;
	int		sizeof_new;

	sizeof_current = get_size(format_var->length);
	sizeof_new = get_size(new_length);
	if (sizeof_new > sizeof_current)
		format_var->length = new_length;
}

void		get_length(const char *format, t_format *format_var, int *i)
{
	if (format[*i] == 'l' && format[*i + 1] == 'l')
		update_length(format_var, LL);
	else if (format[*i] == 'l')
		update_length(format_var, L);
	else if (format[*i] == 'h' && format[*i + 1] == 'h')
		update_length(format_var, HH);
	else if (format[*i] == 'h')
		update_length(format_var, H);
	else if (format[*i] == 'j')
		update_length(format_var, J);
	else if (format[*i] == 'z')
		update_length(format_var, Z);
	else
		format_var->length = NO_FLAG;
	if (format_var->length == HH || format_var->length == LL)
		(*i) += 2;
	else if (format_var->length != NO_FLAG)
		(*i)++;
}

void		get_width(const char *format, t_format *format_var, int *i, va_list ap)
{
	int		res;

	if (format[*i] >= '1' && format[*i] <= '9')
	{
		res = ft_atoi(format + *i);
		*i += ft_intlen(res);
		format_var->width = res;
	}
	else if (format[*i] == '*')
	{
		(*i)++;
		format_var->width = va_arg(ap, int);
		if (format_var->width < 0)
		{
			format_var->minus_flag = 1;
			format_var->width = -format_var->width;
		}
	}
}

void		get_star_width(const char *format, t_format *format_var, int *i, va_list ap)
{
	if (format[*i] == '*')
	{
		(*i)++;
		format_var->width = va_arg(ap, int);
		if (format_var->width < 0)
		{
			format_var->minus_flag = 1;
			format_var->width = -format_var->width;
		}
	}
}
