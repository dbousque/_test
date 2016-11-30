

#include "ft_p_client.h"

char	char_in_str(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_strcpy(char *str1, char *str2, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		str1[i] = str2[i];
		i++;
	}
}