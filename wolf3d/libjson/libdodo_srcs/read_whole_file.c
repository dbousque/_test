/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_whole_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 15:57:53 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 15:58:14 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

char	*read_error(char *error, char err)
{
	*error = err;
	return (NULL);
}

char	*read_whole_file(char *filename, char *error, int max_size,
																int *file_size)
{
	char	*res;
	char	buf[BUF_SIZE];
	int		size;
	int		ret;
	int		fd;

	*error = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (read_error(error, 1));
	size = 0;
	while ((ret = read(fd, buf, BUF_SIZE)) > 0)
	{
		size += ret;
		if (size > max_size)
			return (read_error(error, 3));
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (read_error(error, 1));
	if (!(res = (char*)malloc(sizeof(char) * (size + 1))) || read(fd, res, size) < 0)
		return (read_error(error, 2));
	res[size] = '\0';
	*file_size = size;
	return (res);
}
