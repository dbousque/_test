

#include "push_swap.h"

char	twice_same(int argc, int *nbs)
{
	int		i;
	int		x;

	i = 0;
	while (i < argc)
	{
		x = 0;
		while (x < argc)
		{
			if (i != x && nbs[i] == nbs[x])
				return (1);
			x++;
		}
		i++;
	}
	return (0);
}

char	invalid_char_in(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '-')
		str++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9' || (str[0] == '0' && ft_strlen(str) > 1))
			return (1);
		i++;
	}
	return (0);
}

char	too_big_len_ten(char *str, char signe, int len)
{
	int		i;
	char	*int_max;

	int_max = "2147483647";
	i = 0;
	while (i < len)
	{
		if (i == 9)
		{
			if (str[i] > '8' || (signe == 0 && str[i] > '7'))
				return (1);
		}
		else if (str[i] > int_max[i])
			return (1);
		i++;
	}
	return (0);
}

char	too_big_for_int(char *str)
{
	int		len;
	char	signe;

	signe = 0;
	if (str[0] == '-')
	{
		signe = 1;
		str++;
	}
	len = ft_strlen(str);
	if (len > 10)
		return (1);
	else if (len == 10)
		return (too_big_len_ten(str, signe, len));
	return (0);
}

int		*get_nbs(int argc, char **argv)
{
	int		*nbs;
	int		i;

	if (!(nbs = (int*)malloc(sizeof(int) * (argc - 1))))
		return (NULL);
	i = 1;
	while (i < argc)
	{
		if (invalid_char_in(argv[i]) || too_big_for_int(argv[i]))
		{
			free(nbs);
			return (NULL);
		}
		nbs[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	return (nbs);
}
