

#include "otool.h"

void	print_n_char(char c, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
}

void	ft_putstrn(char *str, int n)
{
	write(1, str, n);
}

char	ft_streq(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (!str1[i] && !str2[i])
		return (1);
	return (0);
}