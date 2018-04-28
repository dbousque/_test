/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_whole_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 15:57:53 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 18:12:27 by dbousque         ###   ########.fr       */
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
	char	*r;
	char	buf[BUF_SIZE];
	int		s[3];

	*error = 0;
	s[2] = open(filename, O_RDONLY);
	if (s[2] < 0)
		return (read_error(error, 1));
	s[0] = 0;
	while ((s[1] = read(s[2], buf, BUF_SIZE)) > 0)
	{
		s[0] += s[1];
		if (s[0] > max_size)
			return (read_error(error, 3));
	}
	close(s[2]);
	s[2] = open(filename, O_RDONLY);
	if (s[2] < 0)
		return (read_error(error, 1));
	if (!(r = malloc(sizeof(char) * (s[0] + 1))) || read(s[2], r, s[0]) < 0)
		return (read_error(error, 2));
	r[s[0]] = '\0';
	*file_size = s[0];
	return (r);
}
