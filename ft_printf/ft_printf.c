

#include "ft_printf.h"



#include <stdio.h>

int		arg_putnbr(va_list ap, char flag)
{
	long long	res;
	int			length;

	if (flag == L)
		res = va_arg(ap, long);
	else if (flag == LL)
		res = va_arg(ap, long long);
	else if (flag == H)
		res = (short)va_arg(ap, int);
	else if (flag == HH)
		res = (char)va_arg(ap, int);
	else if (flag == J)
		res = va_arg(ap, intmax_t);
	else if (flag == Z)
		res = va_arg(ap, size_t);
	else
		res = va_arg(ap, int);
	length = ft_putlonglong(res);
	return (length);
}

int		arg_putnbr_long(va_list ap, char flag)
{
	long long	res;
	int			length;

	if (flag == L || flag == LL)
		res = va_arg(ap, long long);
	else
		res = va_arg(ap, long);
	length = ft_putlonglong(res);
	return (length);
}

int		arg_putnbr_un(va_list ap, char flag)
{
	unsigned long long	res;
	int					length;

	if (flag == L)
		res = va_arg(ap, unsigned long);
	else if (flag == LL)
		res = va_arg(ap, unsigned long long);
	else if (flag == H)
		res = (unsigned short)va_arg(ap, unsigned int);
	else if (flag == HH)
		res = (unsigned char)va_arg(ap, unsigned int);
	else if (flag == J)
		res = va_arg(ap, uintmax_t);
	else if (flag == Z)
		res = va_arg(ap, size_t);
	else
		res = va_arg(ap, unsigned int);
	length = ft_putlonglong_un(res);
	return (length);
}

int		arg_putnbr_un_long(va_list ap, char flag)
{
	unsigned long long	res;
	int					length;

	if (flag == L || flag == LL)
		res = va_arg(ap, unsigned long long);
	else
		res = va_arg(ap, unsigned long);
	length = ft_putlonglong_un(res);
	return (length);
}

int		arg_putchar(va_list ap, char flag)
{
	char	res;
	wchar_t	res2;
	int		length;

	length = 1;
	if (flag == L)
	{
		res2 = va_arg(ap, wchar_t);
		length = ft_put_wchar(res2);
	}
	else
	{
		res = va_arg(ap, int);
		ft_putchar((unsigned char)res);
	}
	return (length);
}

int		arg_putwchar(va_list ap, char flag)
{
	wchar_t	res;

	(void)flag;
	res = va_arg(ap, wchar_t);
	return (ft_put_wchar(res));
}

int		arg_putunicode(va_list ap, char flag)
{
	wchar_t	*res;
	int		length;
(void)flag;
	res = va_arg(ap, wchar_t*);
	if (res)
		length = ft_putunicode(res);
	else
	{
		ft_putstr("(null)");
		return (6);
	}
	return (length);
}

int		arg_putstr(va_list ap, char flag)
{
	char	*res;

	if (flag == L)
		return (arg_putunicode(ap, flag));
	res = va_arg(ap, char*);
	if (res)
		ft_putstr(res);
	else
	{
		ft_putstr("(null)");
		return (6);
	}
	return (ft_strlen(res));
}

int		arg_putaddr(va_list ap, char flag)
{
	void	*res;
	int		length;

	(void)flag;
	res = va_arg(ap, void*);
	length = ft_putaddr(res, 1);
	return (length);
}

int		arg_putoctal(va_list ap, char flag)
{
	unsigned long long	res;
	uintmax_t			res6;
	size_t				res7;
	int					length;

	(void)res6;
	(void)res7;
	if (flag == L)
		res = va_arg(ap, unsigned long);
	else if (flag == LL)
		res = va_arg(ap, unsigned long long);
	else if (flag == H)
		res = (unsigned short)va_arg(ap, unsigned int);
	else if (flag == HH)
		res = (unsigned char)va_arg(ap, unsigned int);
	else if (flag == J)
		res = va_arg(ap, uintmax_t);
	else if (flag == Z)
		res = va_arg(ap, size_t);
	else
		res = va_arg(ap, unsigned int);
	length = ft_putoctal_un(res);
	return (length);
}

int		arg_putoctal_long(va_list ap, char flag)
{
	unsigned long long	res;
	int					length;

	if (flag == L || flag == LL)
		res = va_arg(ap, unsigned long long);
	else
		res = va_arg(ap, unsigned long);
	length = ft_putoctal_un(res);
	return (length);
}

int		arg_puthexa(va_list ap, char flag)
{
	unsigned long long	res;
	int					length;

	if (flag == L)
		res = va_arg(ap, unsigned long);
	else if (flag == LL)
		res = va_arg(ap, unsigned long long);
	else if (flag == H)
		res = (unsigned short)va_arg(ap, unsigned int);
	else if (flag == HH)
		res = (unsigned char)va_arg(ap, unsigned int);
	else if (flag == J)
		res = va_arg(ap, uintmax_t);
	else if (flag == Z)
		res = va_arg(ap, size_t);
	else
		res = va_arg(ap, unsigned int);
	length = ft_puthexa(res);
	return (length);
}

int		arg_puthexa_maj(va_list ap, char flag)
{
	unsigned long long	res;
	int					length;

	if (flag == L)
		res = va_arg(ap, unsigned long);
	else if (flag == LL)
		res = va_arg(ap, unsigned long long);
	else if (flag == H)
		res = (unsigned short)va_arg(ap, unsigned int);
	else if (flag == HH)
		res = (unsigned char)va_arg(ap, unsigned int);
	else if (flag == J)
		res = va_arg(ap, uintmax_t);
	else if (flag == Z)
		res = va_arg(ap, size_t);
	else
		res = va_arg(ap, unsigned int);
	length = ft_puthexa_maj(res);
	return (length);
}

int		print_arg(char c, va_list ap, int *i, char flag)
{
	int		length;

	(*i)++;
	length = 0;
	if (c == 'd' || c == 'i')
		length = arg_putnbr(ap, flag);
	else if (c == 'c')
		length = arg_putchar(ap, flag);
	else if (c == 's')
		length = arg_putstr(ap, flag);
	else if (c == 'u')
		length = arg_putnbr_un(ap, flag);
	else if (c == 'p')
		length = arg_putaddr(ap, flag);
	else if (c == 'o')
		length = arg_putoctal(ap, flag);
	else if (c == 'x')
		length = arg_puthexa(ap, flag);
	else if (c == 'X')
		length = arg_puthexa_maj(ap, flag);
	else if (c == 'S')
		length = arg_putunicode(ap, flag);
	else if (c == 'D')
		length = arg_putnbr_long(ap, flag);
	else if (c == 'O')
		length = arg_putoctal_long(ap, flag);
	else if (c == 'U')
		length = arg_putnbr_un_long(ap, flag);
	else if (c == 'C')
		length = arg_putwchar(ap, flag);
	return (length);
}

char	get_flag(const char *format, int *i)
{
	char	res;

	res = NO_FLAG;
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

	length = 0;
	if (format)
		va_start(ap, format);
	i = 0;
	while (format && format[i])
	{
		if (format[i] == '%' && format[i + 1] != '%')
		{
			if ((flag = get_flag(format, &i)) == NO_FLAG)
				length += print_arg(format[i + 1], ap, &i, NO_FLAG);
			else
				length += print_arg(format[i + 1], ap, &i, flag);
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
	(void)lol2;
	(void)lol;
	ft_printf("1 : %S\n", L"saluté");//L"米");
	printf("2 : %S\n", L"saluté");
	printf("%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S",
	L"Α α", L"Β β", L"Γ γ", L"Δ δ", L"Ε ε", L"Ζ ζ", L"Η η", L"Θ θ", L"Ι ι", L"Κ κ", L"Λ λ", L"Μ μ",
	L"Ν ν", L"Ξ ξ", L"Ο ο", L"Π π", L"Ρ ρ", L"Σ σ", L"Τ τ", L"Υ υ", L"Φ φ", L"Χ χ", L"Ψ ψ", L"Ω ω", L"");
	//ft_printf(inp, nb, -200, 0, -150, 0, -1, 260, long_int);
	//printf(inp, nb, -200, 0, -150, 0, -1, 260, long_int);
	return (0);
}*/
