

#include "ft_printf.h"

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

	valid = "dDioOuUxXpcCsSbr";
	i = 0;
	while (valid[i])
	{
		if (valid[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char		ft_isupper(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

char		is_other_maj(char c)
{
	if (is_valid_specifier(c))
		return (0);
	if (ft_isupper(c) || c == '%')
		return (1);
	return (0);
}
