/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 19:07:04 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/03 16:18:31 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	ft_add_to_res(char *res, t_list *tmp, int *length)
{
	int		i;
	char	*content;

	i = 0;
	content = tmp->content;
	while (content[i])
	{
		res[*length + i] = content[i];
		i++;
	}
	*length += i;
}

static char	*ft_lst_to_array(t_list *lst)
{
	char	*res;
	int		length;
	t_list	*tmp;

	tmp = lst;
	length = 0;
	while (tmp)
	{
		length += (int)tmp->content_size - 1;
		tmp = tmp->next;
	}
	res = (char*)malloc(sizeof(char) * (length + 1));
	res[length] = '\0';
	tmp = lst;
	length = 0;
	while (tmp)
	{
		ft_add_to_res(res, tmp, &length);
		tmp = tmp->next;
	}
	free(tmp);
	tmp = NULL;
	return (res);
}

char		*ft_read_file(char *filename)
{
	int		fd;
	char	buf[BUF_SIZE + 1];
	t_list	*lstend;
	t_list	*lst;
	int		ret;

	lst = NULL;
	lstend = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	ret = read(fd, buf, BUF_SIZE);
	if (ret < 0)
		return (NULL);
	buf[ret] = '\0';
	while (ret > 0)
	{
		ft_lstaddend(&lstend, ft_lstnew(ft_strdup(buf), ret + 1));
		if (lst == NULL)
			lst = lstend;
		ret = read(fd, buf, BUF_SIZE);
		buf[ret] = '\0';
	}
	return (ft_lst_to_array(lst));
}

int			ft_valid_file(char *file_content)
{
	int		i;

	i = 0;
	while (file_content[i])
	{
		if ((i - (i / 21)) % 5 == 4 || (i + 1) % 21 == 0)
		{
			if (file_content[i] != '\n')
				return (0);
		}
		else if (file_content[i] != '.' && file_content[i] != '#')
			return (0);
		i++;
	}
	if ((i + 1) % 21 != 0)
		return (0);
	return (1);
}
