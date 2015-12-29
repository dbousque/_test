

#include "ft_printf.h"






#include <stdio.h>

void		append_precision_to_value(char **value, t_format *format_var, int *length)
{
	char	*tmp;
	int		val_len;
	int		val_len_without_sign;
	int		res_len;
	int		i;
	int		x;

	if (is_other_maj(format_var->specifier) || format_var->specifier == 'd' || format_var->specifier == 'D' || format_var->specifier == 'i'
		|| format_var->specifier == 'o' || format_var->specifier == 'O' || format_var->specifier == 'u'
		|| format_var->specifier == 'U' || format_var->specifier == 'x' || format_var->specifier == 'X' || format_var->specifier == 'p' || format_var->specifier == 'b')
	{
		if (!is_other_maj(format_var->specifier) && format_var->precision == 0 && ((format_var->unsigned_val && format_var->u_value == 0) || (format_var->unsigned_val == 0 && format_var->value == 0)))
		{
			free(*value);
			*value = (char*)malloc(sizeof(char));
			(*value)[0] = '\0';
			*length = 0;
		}
		else
		{
			val_len = *length;
			val_len_without_sign = (format_var->has_sign ? val_len - 1 : val_len);
			if (format_var->precision > val_len_without_sign)
			{
				res_len = format_var->precision + (val_len - val_len_without_sign);
				*length += res_len - val_len;
				if ((tmp = (char*)malloc(sizeof(char) * (format_var->precision + res_len + 1))))
				{
					tmp[res_len] = '\0';
					i = 0;
					if (format_var->neg_val == 1 || format_var->has_sign)
					{
						tmp[0] = (*value)[0];
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
	else if ((format_var->specifier == 'r' || format_var->specifier == 's' || format_var->specifier == 'S') && format_var->precision >= 0 && format_var->precision < (int)ft_strlen(*value))
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

	val_len = *length + decal;
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
	else if (format_var->sharp_flag == 1 && (format_var->u_value != 0 || (format_var->precision != -1 && format_var->specifier != 'x')))
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

void		prepend_plus_space_flags(char **value, t_format *format_var, int *length)
{
	char	*tmp;

	if ((format_var->plus_flag || format_var->space_flag) && !format_var->neg_val)
	{
		format_var->has_sign = 1;
		if ((tmp = (char*)malloc(sizeof(char) * (*length + 2))))
		{
			tmp[*length + 1] = '\0';
			tmp[0] = (format_var->plus_flag ? '+' : ' ');
			ft_memcpy(tmp + 1, *value, *length);
			free(*value);
			*value = tmp;
			(*length)++;
		}
		else
			*value = NULL;
	}
}

int			get_decal(t_format *format)
{
	int		decal;

	decal = (format->specifier == 'p' && format->char_to_fill == '0' ? 2 : 0);
	if (format->char_to_fill == '0' && decal == 0 && format->sharp_flag == 1)
	{
		if (format->specifier == 'o' || format->specifier == 'O')
			decal = 1;
		else if (format->specifier == 'x' || format->specifier == 'X')
			decal = 2;
	}
	return (decal);
}

int			print_format(t_format *format, va_list ap)
{
	char	*value;
	int		length;
	int		decal;
	int		o_done;

	o_done = 0;
	decal = get_decal(format);
	length = get_arg(&value, ap, format);
	if (format->neg_val == 1)
		format->has_sign = 1;
	if (format->specifier == 'd' || format->specifier == 'D' || format->specifier == 'i' || format->specifier == 'b')
		prepend_plus_space_flags(&value, format, &length);
	if (format->sharp_flag && (format->specifier == 'o' || format->specifier == 'O') && format->precision != 0)
	{
		o_done = 1;
		add_prefix_for_addresses_n_sharp(&value, format, &length);
	}
	if (is_valid_specifier(format->specifier))
		append_precision_to_value(&value, format, &length);
	if (!format->minus_flag)
	{
		if (!o_done && format->char_to_fill == ' ')
			add_prefix_for_addresses_n_sharp(&value, format, &length);
		ajust_value_to_width(&value, format, &length, decal);
		if (!o_done && format->char_to_fill == '0')
			add_prefix_for_addresses_n_sharp(&value, format, &length);
	}
	else
	{
		if (!o_done)
			add_prefix_for_addresses_n_sharp(&value, format, &length);
		ajust_value_to_width_minus(&value, format, &length);
	}
	ft_putstr2(value, length);
	if (value)
		free(value);
	value = NULL;
	return (length);
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
	if (format)
		va_start(ap, format);
	i = 0;
	while (format && format[i])
	{
		if (format[i] == '{')
			ft_change_color_if_asked(format, &i);
		if (format[i] == '%' && format[i + 1] != '%')
		{
			format_var = new_format();
			if (parse_format(format, format_var, &i, ap) != -1)
				length += print_format(format_var, ap);
			else
				i--;
			if (format_var)
				free_format(format_var);
		}
		else
		{
			if (format[i] == '%')
				i++;
			ft_putchar(format[i]);
			length++;
		}
		if (format[i])
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
	inp = (char*)malloc(sizeof(char) * 8);
	inp[7] = '\0';
	inp[0] = 'a';
	inp[1] = 23;
	inp[2] = 27;
	inp[3] = 'b';
	inp[4] = 12;
	inp[5] = 4;
	inp[6] = 'c';
	nb = (unsigned long long)-200000000000;
	nb2 = 0;
	i = -1;
	long_int = 990000000000000000;
	lol2 = NULL;
	(void)lol;
	//printf("%d\n", printf("{salut : %#-0+.12d}", 12));
	printf("%d\n", ft_printf("{magenta} SALUT !!!{eoc}", ""));
	//printf("%d\n", printf("{%15.4d}", -424242));
	//printf("%d\n", ft_printf("{%15.4d}", -424242));
	//printf("%-18p\n", &i);
	//ft_printf("%-18p\n", &i);
	//ft_printf("%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S",
	//L"Α α", L"Β β", L"Γ γ", L"Δ δ", L"Ε ε", L"Ζ ζ", L"Η η", L"Θ θ", L"Ι ι", L"Κ κ", L"Λ λ", L"Μ μ",
	//L"Ν ν", L"Ξ ξ", L"Ο ο", L"Π π", L"Ρ ρ", L"Σ σ", L"Τ τ", L"Υ υ", L"Φ φ", L"Χ χ", L"Ψ ψ", L"Ω ω", L"");
	//ft_printf(inp, nb, -200, 0, -150, 0, -1, 260, long_int);
	//printf(inp, nb, -200, 0, -150, 0, -1, 260, long_int);
	return (0);
}
