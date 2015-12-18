

#include "ft_printf.h"



#include <stdio.h>

void	arg_putnbr(va_list ap)
{
	int		res;

	res = va_arg(ap, int);
	ft_putnbr(res);
}

void	arg_putnbr_un(va_list ap)
{
	unsigned int	res;

	res = va_arg(ap, unsigned int);
	ft_putnbr_un(res);
}

void	arg_putchar(va_list ap)
{
	char	res;

	res = va_arg(ap, int);
	ft_putchar((unsigned char)res);
}

void	arg_putstr(va_list ap)
{
	char	*res;

	res = va_arg(ap, char*);
	ft_putstr(res);
}

void	arg_putaddr(va_list ap)
{
	void	*res;

	res = va_arg(ap, void*);
	ft_putaddr(res);
}

void	arg_putoctal(va_list ap)
{
	long	res;

	res = va_arg(ap, long);
	ft_putoctal((unsigned int)res);
}

void	print_arg(char c, va_list ap, int *i)
{
	(*i)++;
	if (c == 'd')
		arg_putnbr(ap);
	else if (c == 'c')
		arg_putchar(ap);
	else if (c == 's')
		arg_putstr(ap);
	else if (c == 'u')
		arg_putnbr_un(ap);
	else if (c == 'p')
		arg_putaddr(ap);
	else if (c == 'o')
		arg_putoctal(ap);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;

	va_start(ap, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
			print_arg(format[i + 1], ap, &i);
		else
			ft_putchar(format[i]);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int				nb;
	unsigned int	nb2;
	char			*inp;

	(void)argc;
	(void)argv;
	inp = "lol : %d, %c, %u, %p, %o\n";
	nb = 5;
	nb2 = 0;
	ft_printf("This is a simple test.");
	printf("This is a simple test.");
	//ft_printf(inp, nb, -200, -150, inp, -1);
	//printf(inp, nb, -200, -150, inp, -1);
}
