

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

char	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

char			*build_file_path2(char *dir_path, char *file_name,
											char *res, char add_slash)
{
	size_t	i;
	size_t	name_len;

	i = 0;
	while (dir_path[i])
	{
		res[i] = dir_path[i];
		i++;
	}
	name_len = i + add_slash;
	if (add_slash)
		res[i] = '/';
	i = 0;
	while (file_name[i])
	{
		res[name_len + i] = file_name[i];
		i++;
	}
	return (res);
}

char			*build_file_path(char *dir_path, char *file_name)
{
	size_t	i;
	size_t	name_len;
	char	*res;
	char	add_slash;

	name_len = ft_strlen(file_name);
	add_slash = 1;
	i = 0;
	while (dir_path[i])
		i++;
	if (i == 0 || dir_path[i - 1] == '/')
		add_slash = 0;
	if (!(res = (char*)malloc(sizeof(char) * (i + add_slash + name_len + 1))))
		return (NULL);
	res[i + add_slash + name_len] = '\0';
	return (build_file_path2(dir_path, file_name, res, add_slash));
}