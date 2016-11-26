

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

char	*ft_strconcat(char *str1, char *str2, size_t size1, size_t size2)
{
	char	*res;
	size_t	i;
	size_t	len;

	if (!(res = (char*)malloc(sizeof(char) * (size1 + size2))))
		return (NULL);
	i = 0;
	len = 0;
	while (i < size1)
	{
		res[len] = str1[i];
		i++;
		len++;
	}
	i = 0;
	while (i < size2)
	{
		res[len] = str2[i];
		i++;
		len++;
	}
	return (res);
}