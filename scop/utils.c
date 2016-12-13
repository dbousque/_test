

#include "myopengl.h"

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

char	*append_buf_to_res(char *res, size_t size, char *buffer, int ret)
{
	char	*new_res;
	size_t 	i;
	size_t	start;

	if (!(new_res = (char*)malloc(sizeof(char) * (size + ret + 1))))
	{
		ft_putstr("malloc error\n");
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		new_res[i] = res[i];
		i++;
	}
	start = 0;
	while (start < (size_t)ret)
	{
		new_res[i + start] = buffer[start];
		start++;
	}
	new_res[i + start] = '\0';
	return (new_res);
}

char	*read_file(char *filename, size_t max_size)
{
	char	*res;
	size_t	size;
	int		fd;
	int		ret;
	char	buffer[READ_BUFFER_LEN];

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_putstr("could not open file\n");
		return (NULL);
	}
	size = 0;
	while ((ret = read(fd, buffer, READ_BUFFER_LEN - 1)) > 0
			&& size + ret < max_size)
	{
		res = append_buf_to_res(res, size, buffer, ret);
		if (!res)
			return (NULL);
		size += ret;
	}
	if (ret == -1 || size + ret > max_size)
	{
		ft_putstr("read error\n");
		return (NULL);
	}
	close(fd);
	return (res);
}