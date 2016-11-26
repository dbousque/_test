

#include "ft_p_server.h"

char	*ft_strcpy(char *str)
{
	char	*res;
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	res = (char*)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}