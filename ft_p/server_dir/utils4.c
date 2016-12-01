

#include "ft_p_server.h"

void	ft_strcpy2(char *str1, char *str2, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		str1[i] = str2[i];
		i++;
	}
}