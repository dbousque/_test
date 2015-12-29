

#include "ft_printf.h"

void		get_start_flags(const char *format, t_format *format_var, int *i)
{
	while (format[*i] == '-')
		get_minus_flag(format, format_var, i);
	while (format[*i] == ' ')
		get_space_flag(format, format_var, i);
	while (format[*i] == '+')
		get_plus_flag(format, format_var, i);
	while (format[*i] == ' ')
		get_space_flag(format, format_var, i);
	while (format[*i] == '+')
		get_plus_flag(format, format_var, i);
	while (format[*i] == '#')
		get_sharp_flag(format, format_var, i);
	while (format[*i] == '-')
		get_minus_flag(format, format_var, i);
	while (format[*i] == '#')
		get_sharp_flag(format, format_var, i);
	while (format[*i] == '0')
		get_zero_flag(format, format_var, i);
	while (format[*i] == '+')
		get_plus_flag(format, format_var, i);
}

void		get_following_flags(const char *format, t_format *format_var, int *i, va_list ap)
{
	if (format_var->minus_flag == 0)
	{
		while (format[*i] == '-')
			get_minus_flag(format, format_var, i);
	}
	if (format_var->sharp_flag == 0)
	{
		while (format[*i] == '#')
			get_sharp_flag(format, format_var, i);
	}
	while (format[*i] == '0')
		get_zero_flag(format, format_var, i);
	while (format[*i] == ' ')
		get_space_flag(format, format_var, i);
	get_width(format, format_var, i, ap);
	while (format[*i] == '*')
		get_star_width(format, format_var, i, ap);
}

void		get_precision_n_length(const char *format, t_format *format_var, int *i, va_list ap)
{
	while (format[*i] == '.')
		get_precision(format, format_var, i, ap);
	while (format[*i] == 'h' || format[*i] == 'l' || format[*i] == 'j' || format[*i] == 'z')
		get_length(format, format_var, i);
	if (format_var->precision == -1)
	{
		while (format[*i] == '.')
			get_precision(format, format_var, i, ap);
	}
	get_width(format, format_var, i, ap);
}

void		get_end_flags(const char *format, t_format *format_var, int *i, va_list ap)
{
	while (format[*i] == ' ')
		get_space_flag(format, format_var, i);
	while (format[*i] == '+')
		get_plus_flag(format, format_var, i);
	while (format[*i] == '#')
		get_sharp_flag(format, format_var, i);
	while (format[*i] == '0')
		get_zero_flag(format, format_var, i);
	while (format[*i] == '+')
		get_plus_flag(format, format_var, i);
	get_width(format, format_var, i, ap);
}

int			parse_format(const char *format, t_format *format_var, int *i, va_list ap)
{
	(*i)++;
	get_start_flags(format, format_var, i);
	get_following_flags(format, format_var, i, ap);
	get_width(format, format_var, i, ap);
	get_precision_n_length(format, format_var, i, ap);
	get_end_flags(format, format_var, i, ap);
	while (invalid_end(format[*i]))
		(*i)++;
	if (!is_valid_specifier(format[*i]) && !is_other_maj(format[*i]))
		return (-1);
	format_var->specifier = format[*i];
	if (format_var->width > format_var->precision && format_var->precision > -1 && !bad_specifier(format_var->specifier))
		format_var->char_to_fill = ' ';
	return (0);
}
