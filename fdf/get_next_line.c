/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <dbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 11:13:21 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/09 13:59:27 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		ft_tmp_function(int *len, t_list *list, t_file **f, int *st)
{
	if (*f)
	{
		*len = 0;
		*st = 0;
		while (list)
		{
			*len += ft_strlen(list->content);
			list = list->next;
		}
		if ((*f)->content)
			*st = ft_strlen((*f)->content);
		if (*st > 0)
			*len += *st;
	}
	else
	{
		while (list && !(*f))
		{
			if (((t_file*)list->content)->fd == *st)
				*f = ((t_file*)list->content);
			list = list->next;
		}
	}
}

static t_file	*ft_find_file(t_list **files, int fd, int *line_ther, int i)
{
	t_file	*file;

	file = NULL;
	ft_tmp_function(&i, *files, &file, &fd);
	if (!file)
	{
		if (!(file = (t_file*)malloc(sizeof(t_file))))
			return (NULL);
		file->fd = fd;
		file->content = NULL;
		if (!(*files))
			ft_lstaddend(files, ft_lstnew(file, sizeof(t_file)));
		else
			ft_lstadd(files, ft_lstnew(file, sizeof(t_file)));
		file = (t_file*)((*files)->content);
	}
	if (file->content)
	{
		while (file->content[i] && file->content[i] != '\n')
			i++;
		if (file->content[i] == '\n')
			*line_ther = i;
	}
	return (file);
}

static int		ft_lst_to_array(t_list *list, t_file *file, int return_val)
{
	char	*res;
	int		length;
	int		start;

	if (!list)
		return (return_val);
	ft_tmp_function(&length, list, &file, &start);
	if (!(res = (char*)malloc(sizeof(char) * (length + 1))))
		return (-1);
	res[length] = '\0';
	if (start > 0)
		ft_strncpy(res, file->content, start);
	while (list)
	{
		length = 0;
		while (((char*)list->content)[length])
		{
			res[start + length] = ((char*)list->content)[length];
			length++;
		}
		start += length;
		list = list->next;
	}
	file->content = res;
	return (return_val);
}

static int		ft_read_until_newline(t_file *file, int *ind, int x, t_list *li)
{
	char	buf[BUF_SIZE + 1];
	t_list	*list;
	int		i;
	int		ret;

	list = NULL;
	ret = read(file->fd, buf, BUF_SIZE);
	if (ret < 0)
		return (-1);
	while (ret > 0)
	{
		buf[ret] = '\0';
		ft_lstaddend(&li, ft_lstnew(buf, sizeof(char) * (ret + 1)));
		list = (!list ? li : list);
		i = 0;
		while (buf[i] && buf[i] != '\n')
			i++;
		*ind = x + i + (file->content ? ft_strlen(file->content) : 0);
		if (buf[i] == '\n')
			return (ft_lst_to_array(list, file, 1));
		x += ret;
		ret = read(file->fd, buf, BUF_SIZE);
	}
	*ind = x + (file->content ? ft_strlen(file->content) : 0);
	return (ft_lst_to_array(list, file, 0));
}

int				get_next_line(int const fd, char **line)
{
	static t_list	*files = NULL;
	t_file			*file;
	int				res;
	int				ind;

	ind = -1;
	file = ft_find_file(&files, fd, &ind, 0);
	if (!file || !line)
		return (-1);
	res = 1;
	if (ind == -1)
		res = ft_read_until_newline(file, &ind, 0, NULL);
	if (res == -1)
		return (-1);
	*line = (char*)malloc(sizeof(char) * (ind + 1));
	(*line)[ind] = '\0';
	if (file->content)
		ft_strncpy(*line, file->content, ind);
	if (file->content && file->content[ind])
		file->content += ind + 1;
	else
		file->content = NULL;
	return (res);
}
