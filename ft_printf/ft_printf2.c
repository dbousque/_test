

#include "ft_printf.h"






#include <stdio.h>

int		ft_intlen(int nb)
{
	int		length;

	if (nb == 0)
		return (1);
	length = 0;
	if (nb < 0)
		length = 1;
	while (nb != 0)
	{
		length++;
		nb /= 10;
	}
	return (length);
}

char		is_valid_specifier(char c)
{
	char	*valid;
	int		i;

	valid = "dDioOuUxXpcCsS";
	i = 0;
	while (valid[i])
	{
		if (valid[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void		append_precision_to_value(char **value, t_format *format_var, int *length)
{
	char	*tmp;
	int		val_len;
	int		val_len_without_sign;
	int		res_len;
	int		i;
	int		x;

	if (format_var->specifier == 'd' || format_var->specifier == 'D' || format_var->specifier == 'i'
		|| format_var->specifier == 'o' || format_var->specifier == 'O' || format_var->specifier == 'u'
		|| format_var->specifier == 'U' || format_var->specifier == 'x' || format_var->specifier == 'X' || format_var->specifier == 'p')
	{
		if (format_var->precision == 0 && ((format_var->unsigned_val && format_var->u_value == 0) || (format_var->unsigned_val == 0 && format_var->value == 0)))
		{
			free(*value);
			*value = (char*)malloc(sizeof(char));
			(*value)[0] = '\0';
			*length = 0;
		}
		else
		{
			val_len = *length;//ft_strlen(*value);
			val_len_without_sign = (format_var->has_sign ? val_len - 1 : val_len);
			if (format_var->precision > val_len_without_sign)
			{
				res_len = format_var->precision + (val_len - val_len_without_sign);
				*length += res_len - val_len;
				if ((tmp = (char*)malloc(sizeof(char) * (format_var->precision + res_len + 1))))
				{
					tmp[res_len] = '\0';
					i = 0;
					if (format_var->neg_val == 1)
					{
						tmp[0] = '-';
						i = 1;
					}
					x = i;
					while (i < res_len - val_len_without_sign)
					{
						tmp[i] = '0';
						i++;
					}
					while (i < res_len)
					{
						tmp[i] = (*value)[x];
						i++;
						x++;
					}
					free(*value);
					*value = tmp;
				}
			}
		}
	}
	else if ((format_var->specifier == 's' || format_var->specifier == 'S') && format_var->precision >= 0 && format_var->precision < (int)ft_strlen(*value))
	{
		if ((tmp = (char*)malloc(sizeof(char) * format_var->precision + 1)))
		{
			tmp[format_var->precision] = '\0';
			tmp = ft_strncpy(tmp, *value, format_var->precision);
			free(*value);
			*value = tmp;
			*length = format_var->precision;
		}
	}
}

void		ajust_value_to_width_minus(char **value, t_format *format_var, int *length)
{
	char	*tmp;

	if (format_var->width > *length)
	{
		if ((tmp = (char*)malloc(sizeof(char) * (format_var->width + 1))))
		{
			tmp[format_var->width] = '\0';
			ft_memcpy(tmp, *value, *length);
			while (*length < format_var->width)
			{
				tmp[*length] = ' ';
				(*length)++;
			}
			free(*value);
			*value = tmp;
		}
		else
			*value = NULL;
	}
}

void		ajust_value_to_width(char **value, t_format *format_var, int *length, int decal)
{
	int		val_len;
	int		ori_precision;
	char	ori_specifier;
	char	*tmp;
	int		i;

	val_len = *length + decal;//ft_strlen(*value);
	if (format_var->width > val_len)
	{
		if (format_var->char_to_fill == '0')
		{
			ori_precision = format_var->precision;
			ori_specifier = format_var->specifier;
			if (format_var->has_sign == 1)
				format_var->precision = format_var->width - 1;
			else
				format_var->precision = format_var->width;
			format_var->precision -= decal;
			format_var->specifier = 'd';
			append_precision_to_value(value, format_var, length);
			format_var->precision = ori_precision;
			format_var->specifier = ori_specifier;
		}
		else
		{
			if ((tmp = (char*)malloc(sizeof(char) * (format_var->width + 1))))
			{
				tmp[format_var->width] = '\0';
				i = val_len;
				while (val_len < format_var->width)
				{
					tmp[val_len - i] = ' ';
					val_len++;
					(*length)++;
				}
				ft_memcpy(tmp + (val_len - i), *value, format_var->width - (val_len - i));
				free(*value);
				*value = tmp;
			}
			else
				*value = NULL;
		}
	}
}

void		get_precision(const char *format, t_format *format_var, int *i)
{
	int		res;

	if (format[*i] == '.' && format[*i + 1] >= '0' && format[*i + 1] <= '9')
	{
		res = ft_atoi(format + *i + 1);
		*i += ft_intlen(res) + 1;
		format_var->precision = res;
	}
	else if (format[*i] == '.')
	{
		(*i)++;
		format_var->precision = 0;
	}
	else
		format_var->precision = -1;
}

void		get_length(const char *format, t_format *format_var, int *i)
{
	if (format[*i] == 'l' && format[*i + 1] == 'l')
		format_var->length = LL;
	else if (format[*i] == 'l')
		format_var->length = L;
	else if (format[*i] == 'h' && format[*i + 1] == 'h')
		format_var->length = HH;
	else if (format[*i] == 'h')
		format_var->length = H;
	else if (format[*i] == 'j')
		format_var->length = J;
	else if (format[*i] == 'z')
		format_var->length = Z;
	else
		format_var->length = NO_FLAG;
	if (format_var->length == HH || format_var->length == LL)
		(*i) += 2;
	else if (format_var->length != NO_FLAG)
		(*i)++;
}

void		get_width(const char *format, t_format *format_var, int *i)
{
	int		res;

	if (format[*i] >= '1' && format[*i] <= '9')
	{
		res = ft_atoi(format + *i);
		*i += ft_intlen(res);
		format_var->width = res;
	}
}

void		get_zero_flag(const char *format, t_format *format_var, int *i)
{
	if (format[*i] == '0')
	{
		format_var->char_to_fill = '0';
		(*i)++;
	}
}

void		get_minus_flag(const char *format, t_format *format_var, int *i)
{
	if (format[*i] == '-')
	{
		format_var->minus_flag = 1;
		(*i)++;
	}
}

void		get_sharp_flag(const char *format, t_format *format_var, int *i)
{
	if (format[*i] == '#')
	{
		format_var->sharp_flag = 1;
		(*i)++;
	}
}

void		get_space_flag(const char *format, t_format *format_var, int *i)
{
	if (format[*i] == ' ')
	{
		format_var->space_flag = 1;
		(*i)++;
	}
}

void		get_plus_flag(const char *format, t_format *format_var, int *i)
{
	if (format[*i] == '+')
	{
		format_var->plus_flag = 1;
		(*i)++;
	}
}

void		add_sharp_prefix(char **value, t_format *format_var, int *length)
{
	char	*tmp;

	if (format_var->specifier == 'o' || format_var->specifier == 'O')
	{
		if ((tmp = (char*)malloc(sizeof(char) * (*length + 2))))
		{
			tmp[*length + 1] = '\0';
			(*length)++;
			tmp[0] = '0';
			ft_strcpy(tmp + 1, *value);
			free(*value);
			*value = tmp;
		}
		else
			*value = NULL;
	}
	else if (format_var->specifier == 'x' || format_var->specifier == 'X')
	{
		if ((tmp = (char*)malloc(sizeof(char) * (*length + 3))))
		{
			tmp[*length + 2] = '\0';
			(*length) += 2;
			tmp[0] = '0';
			tmp[1] = (format_var->specifier == 'x' ? 'x' : 'X');
			ft_strcpy(tmp + 2, *value);
			free(*value);
			*value = tmp;
		}
		else
			*value = NULL;
	}
}

void		add_prefix_for_addresses_n_sharp(char **value, t_format *format_var, int *length)
{
	char	*tmp;
	int		len;

	if (format_var->specifier == 'p')
	{
		len = ft_strlen(*value);
		if ((tmp = (char*)malloc(sizeof(char) * (len + 1))))
		{
			tmp[len] = '\0';
			tmp[0] = '0';
			tmp[1] = 'x';
			ft_strcpy(tmp + 2, *value);
			free(*value);
			*value = tmp;
			*length += 2;
		}
		else
			*value = NULL;
	}
	else if (format_var->sharp_flag == 1 && format_var->u_value != 0)
		add_sharp_prefix(value, format_var, length);
}

void		ft_putstr2(char *str, int length)
{
	int		i;

	i = 0;
	while (i < length)
	{
		ft_putchar(str[i]);
		i++;
	}
}

int			get_decal(t_format *format)
{
	int		decal;

	decal = (format->specifier == 'p' && format->char_to_fill == '0' ? 2 : 0);
	/*if (decal == 0 && format->sharp_flag == 1)
	{
		if (format->specifier == 'o' || format->specifier == 'O')
			decal = 1;
		else if (format->specifier == 'x' || format->specifier == 'X')
			decal = 2;
	}*/
	return (decal);
}

int			print_format(t_format *format, va_list ap)
{
	char	*value;
	int		length;
	int		decal;

	decal = get_decal(format);
	length = get_arg(&value, ap, format);
	if (format->neg_val == 1)
		format->has_sign = 1;
	append_precision_to_value(&value, format, &length);
	if (!format->minus_flag)
	{
		if (format->char_to_fill == ' ')
			add_prefix_for_addresses_n_sharp(&value, format, &length);
		ajust_value_to_width(&value, format, &length, decal);
		if (format->char_to_fill == '0')
			add_prefix_for_addresses_n_sharp(&value, format, &length);
	}
	else
	{
		add_prefix_for_addresses_n_sharp(&value, format, &length);
		ajust_value_to_width_minus(&value, format, &length);
	}
	ft_putstr2(value, length);
	return (length);
}

int			parse_format(const char *format, t_format *format_var, int *i)
{
	(*i)++;
	get_minus_flag(format, format_var, i);
	get_space_flag(format, format_var, i);
	get_plus_flag(format, format_var, i);
	if (format_var->plus_flag == 0)
		get_space_flag(format, format_var, i);
	get_sharp_flag(format, format_var, i);
	get_zero_flag(format, format_var, i);
	if (format_var->minus_flag == 0)
		get_minus_flag(format, format_var, i);
	if (format_var->sharp_flag == 0)
		get_sharp_flag(format, format_var, i);
	get_width(format, format_var, i);
	get_precision(format, format_var, i);
	if (format_var->width > format_var->precision && format_var->precision != -1)
		format_var->char_to_fill = ' ';
	get_length(format, format_var, i);
	if (format_var->precision == -1)
		get_precision(format, format_var, i);
	format_var->specifier = format[*i];
	if (!is_valid_specifier(format[*i]))
		return (-1);
	return (0);
}

void		free_format(t_format *format)
{
	if (format)
		free(format);
	format = NULL;
}

t_format	*new_format(void)
{
	t_format	*format_var;

	if (!(format_var = (t_format*)malloc(sizeof(t_format))))
		return (NULL);
	format_var->char_to_fill = ' ';
	format_var->neg_val = 0;
	format_var->unsigned_val = 0;
	format_var->has_sign = 0;
	format_var->characters = 0;
	format_var->length = -1;
	format_var->width = -1;
	format_var->precision = -1;
	format_var->specifier = -1;
	format_var->plus_flag = 0;
	format_var->sharp_flag = 0;
	format_var->space_flag = 0;
	format_var->minus_flag = 0;
	format_var->value = 0;
	format_var->u_value = 0;
	return (format_var);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;
	int			length;
	t_format	*format_var;

	length = 0;
	format_var = NULL;
	if (format)
		va_start(ap, format);
	i = 0;
	while (format && format[i])
	{
		if (format[i] == '%' && format[i + 1] != '%')
		{
			if (format_var)
				free_format(format_var);
			format_var = new_format();
			if (parse_format(format, format_var, &i) != -1)
				length += print_format(format_var, ap);
			else if (format_var->specifier == '%')
			{
				ft_putchar('%');
				length++;
			}
		}
		else
		{
			if (format[i] == '%')
				i++;
			ft_putchar(format[i]);
			length++;
		}
		i++;
	}
	return (length);
}

int		main(int argc, char **argv)
{
	unsigned long long			nb;
	unsigned long long	nb2;
	char			*inp;
	int				i;
	wchar_t			*lol = L"ру́сский";
	char			*lol2 = "salut";
	long long		long_int;

	(void)argc;
	(void)argv;
	inp = "lol : %hhd, %c, %s, %u, %p, %lO, %X, %llu\n";
	nb = (unsigned long long)-200000000000;
	nb2 = 0;
	i = -1;
	long_int = 990000000000000000;
	lol2 = NULL;
	(void)lol;
	printf("%d\n", printf("{salut : % +d}", 42));
	printf("%d\n", ft_printf("{salut : % +d}", 42));
	//printf("%d\n", printf("{%15.4d}", -424242));
	//printf("%d\n", ft_printf("{%15.4d}", -424242));
	//printf("%-18p\n", &i);
	//ft_printf("%-18p\n", &i);
	//ft_printf("1 : %S\n", L"saluté");//L"米");
	//printf("2 : %S\n", L"saluté");
	//ft_printf("%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S",
	//L"Α α", L"Β β", L"Γ γ", L"Δ δ", L"Ε ε", L"Ζ ζ", L"Η η", L"Θ θ", L"Ι ι", L"Κ κ", L"Λ λ", L"Μ μ",
	//L"Ν ν", L"Ξ ξ", L"Ο ο", L"Π π", L"Ρ ρ", L"Σ σ", L"Τ τ", L"Υ υ", L"Φ φ", L"Χ χ", L"Ψ ψ", L"Ω ω", L"");
	//ft_printf(inp, nb, -200, 0, -150, 0, -1, 260, long_int);
	//printf(inp, nb, -200, 0, -150, 0, -1, 260, long_int);
	return (0);
}
