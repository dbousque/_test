/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_mesh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <dbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 11:21:21 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/09 15:07:32 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include <unistd.h>

#include <stdlib.h>

#include "libft.h"

#include "get_next_line.h"

int		ft_strstrlen(char **strstr)
{
	int		i;

	i = 0;
	while (strstr[i])
		i++;
	return (i);
}

int		ft_lstlen(t_list *list)
{
	int		i;
	
	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	ft_delstr(void *content, size_t size)
{
	ft_strdel((char**)&content);
	content = NULL;
	(void)size;
}

char	ft_validchars(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		*ft_atoistr(char **line, int length)
{
	int		*res;
	int		i;

	if (!(res = (int*)malloc(sizeof(int) * (length + 1))))
		return (NULL);
	res[0] = length;
	i = 0;
	while (i < length)
	{
		if (!ft_validchars(line[i]))
			return (NULL);
		res[i + 1] = ft_atoi(line[i]);
		i++;
	}
	return (res);
}

char	ft_last_elt_not_empty(t_list *list)
{
	while (list->next)
		list = list->next;
	if (ft_strlen((char*)list->content) > 0)
		return (1);
	return (0);
}

int		**ft_lst_to_int_array(t_list *lines)
{
	int		length;
	int		**res;
	char	**tmp;
	int		ind;

	length = ft_lstlen(lines);
	if (length <= 2 || ft_last_elt_not_empty(lines))
		return (NULL);
	if (!(res = (int**)malloc(sizeof(int*) * (length))))
		return (NULL);
	res[length - 1] = NULL;
	length = -1;
	ind = 0;
	while (lines->next)
	{
		tmp = ft_strsplit((char*)lines->content, ' ');
		if (length == -1)
			length = ft_strstrlen(tmp);
		if ((!tmp[0] && lines->next) || length < 2 || ft_strstrlen(tmp) != length)
			return (NULL);
		if (!(res[ind] = ft_atoistr(tmp, length)))
			return (NULL);
		lines = lines->next;
		ind++;
	}
	ft_lstdel(&lines, ft_delstr);
	return (res);
}

int		**ft_get_mesh(char *filename)
{
	int		res;
	int		fd;
	char	**line;
	t_list	*lines;
	t_list	*lines_end;

	lines = NULL;
	lines_end = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!(line = (char**)malloc(sizeof(char*))))
		return (NULL);
	while ((res = get_next_line(fd, line)) > 0)
	{
		ft_lstaddend(&lines_end, ft_lstnew(*line, sizeof(char) * (ft_strlen(*line) + 1)));
		if (!lines)
			lines = lines_end;
	}
	if (res < 0)
		return (NULL);
	if (lines)
		ft_lstaddend(&lines_end, ft_lstnew(*line, sizeof(char) * (ft_strlen(*line) + 1)));
	if (!lines)
		lines = lines_end;
	return (ft_lst_to_int_array(lines));
}
