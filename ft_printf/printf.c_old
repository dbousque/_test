

#include "ft_printf.h"



#include <stdio.h>

int		put_min_width(int min_width, int length, char char_to_fill, int precision, char show_sign, char neg)
{
	int		nb;
	int		added;

	nb = (min_width > 0 ? min_width - length : -min_width - length);
	if (min_width > 0 && precision > length)
		nb -= precision - length;
	if (show_sign == 1 || neg)
		nb--;
	added = nb;
	while (nb > 0)
	{
		ft_putchar(char_to_fill);
		nb--;
	}
	return (added);
}

void	prepend_sign_if_zeros(char **str, char show_sign, char char_to_fill, int *length, char c)
{
	if ((show_sign || (*str)[0] == '-') && char_to_fill == '0')
	{
		if ((*str)[0] == '-' && c != 'c' && c != 'C' && c != 's' && c != 'S')
		{
			(*str)++;
			ft_putchar('-');
		}
		else if ((*str)[0] != '-')
		{
			ft_putchar('+');
			(*length)++;
		}
	}
}

void	prepend_sign_if_precision(char **str, int precision, char show_sign, int *length, char c)
{
	int		str_len;

	str_len = ft_strlen(*str);
	if ((*str)[0] == '-')
		str_len--;
	if (precision > str_len && (c == 'd' || c == 'D' || c == 'x' || c == 'X' || c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'U'))
	{
		if ((*str)[0] == '-')
		{
			(*str)++;
			ft_putchar('-');
		}
		else if (show_sign == 1)
		{
			(*length)++;
			ft_putchar('+');
		}
		while (precision > str_len)
		{
			ft_putchar('0');
			(*length)++;
			precision--;
		}
	}
}

void	sharp(int *length, char c)
{
	ft_putchar('0');
	(*length)++;
	if (c == 'x')
	{
		ft_putchar('x');
		(*length)++;
	}
	else if (c == 'X')
	{
		ft_putchar('X');
		(*length)++;
	}
}

int		print_arg(char c, va_list ap, int *i, char flag, int min_width, char char_to_fill, char prefix, char show_sign, int precision)
{
	int		length;
	char	*str;
	int		added_chars;
	char	neg_nb;
	char	signed_nb;

	(*i)++;
	length = 0;
	added_chars = 0;
	str = NULL;
	length = get_arg(&str, ap, flag, c);
	signed_nb = (c == 'i' || c == 'd' || c == 'D') ? 1 : 0;
	neg_nb = (str[0] == '-' && signed_nb) ? 1 : 0;
	if (precision <= 0)
		prepend_sign_if_zeros(&str, show_sign, char_to_fill, &length, c);
	else
		char_to_fill = ' ';
	if (show_sign && char_to_fill != '0' && signed_nb && !neg_nb && precision <= (int)ft_strlen(str))
		length++;
	if (str && length < min_width)
		added_chars = put_min_width(min_width, length, char_to_fill, precision, show_sign, neg_nb);
	prepend_sign_if_precision(&str, precision, show_sign, &length, c);
	if (show_sign && char_to_fill != '0' && signed_nb && !neg_nb && precision <= (int)ft_strlen(str))
	{
		if (show_sign == -1)
			ft_putchar(' ');
		else if (precision <= (int)ft_strlen(str))
			ft_putchar('+');
	}
	if (str && prefix && (c == 'o' || c == 'O' || c == 'x' || c == 'X') && !(str[0] == '0' && ft_strlen(str) == 1))
		sharp(&length, c);
	if (str)
		ft_putstr(str);
	if (str && min_width < 0 && -min_width > length)
		added_chars = put_min_width(min_width, length, char_to_fill, precision, show_sign, neg_nb);
	return (length + added_chars);
}

int		ft_intlen(int nb)
{
	int		length;

	if (nb == 0)
		return (1);
	length = 0;
	while (nb != 0)
	{
		length++;
		nb /= 10;
	}
	return (length);
}

int		get_min_width(const char *format, int *i, char *char_to_fill, char *prefix, char *show_sign, int *precision)
{
	int		res;
	int		neg;

	res = 0;
	neg = 0;
	if (format[*i + 1] == ' ')
	{
		*show_sign = -1;
		(*i)++;
	}
	if (format[*i + 1] == '+')
	{
		*show_sign = 1;
		(*i)++;
	}
	if (format[*i + 1] == '-')
	{
		neg = 1;
		(*i)++;
	}
	if (format[*i + 1] == '0')
	{
		*char_to_fill = '0';
		(*i)++;
	}
	if (format[*i + 1] == '#')
	{
		*prefix = 1;
		(*i)++;
	}
	if (format[*i + 1] > '0' && format[*i + 1] <= '9')
		res = ft_atoi(format + *i + 1);
	if (res != 0)
		*i += ft_intlen(res);
	if (format[*i + 1] == '.')
	{
		(*i)++;
		*precision = ft_atoi(format + *i + 1);
		(*i) += ft_intlen(*precision);
	}
	if (neg == 1)
		return (-res);
	return (res);
}

char	get_flag(const char *format, int *i, int *min_width, char *char_to_fill, char *prefix, char *show_sign, int *precision)
{
	char	res;

	res = NO_FLAG;
	*min_width = get_min_width(format, i, char_to_fill, prefix, show_sign, precision);
	if (!format[*i + 1])
		res = NO_FLAG;
	else if (format[*i + 1] == 'h' && format[*i + 2] == 'h')
		res = HH;
	else if (format[*i + 1] == 'h')
		res = H;
	else if (format[*i + 1] == 'l' && format[*i + 2] == 'l')
		res = LL;
	else if (format[*i + 1] == 'l')
		res = L;
	else if (format[*i + 1] == 'j')
		res = J;
	else if (format[*i + 1] == 'z')
		res = Z;
	if (res == HH || res == LL)
		*i += 2;
	else if (res != NO_FLAG)
		*i += 1;
	return (res);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	char	flag;
	int		length;
	int		min_width;
	char	char_to_fill;
	char	prefix;
	char	show_sign;
	int		precision;

	show_sign = 0;
	precision = -1;
	prefix = 0;
	char_to_fill = ' ';
	length = 0;
	if (format)
		va_start(ap, format);
	i = 0;
	while (format && format[i])
	{
		if (format[i] == '%' && format[i + 1] != '%')
		{
			if ((flag = get_flag(format, &i, &min_width, &char_to_fill, &prefix, &show_sign, &precision)) == NO_FLAG)
				length += print_arg(format[i + 1], ap, &i, NO_FLAG, min_width, char_to_fill, prefix, show_sign, precision);
			else
				length += print_arg(format[i + 1], ap, &i, flag, min_width, char_to_fill, prefix, show_sign, precision);
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

/*int		main(int argc, char **argv)
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
	printf("%d\n", printf("{%15.4d}", -424242));
	printf("%d\n", ft_printf("{%15.4d}", -424242));
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
}*/
