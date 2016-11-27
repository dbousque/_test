

#include "ft_p_client.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_strcat(char *str1, char *str2, size_t from, size_t len)
{
	size_t	ori_from;

	ori_from = from;
	while (from < ori_from + len)
	{
		str1[from] = str2[from - ori_from];
		from++;
	}
}

char	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
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