/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_mesh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <dbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 11:21:21 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/17 17:38:10 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		res[i + 1] = ft_atoi(line[i]);
		i++;
	}
	return (res);
}

void	ft_initialize_vars(int *ind, int *length, int **res)
{
	res[*length - 1] = NULL;
	*length = -1;
	*ind = 0;
}

int		**ft_lst_to_int_array(t_list *lines)
{
	int		len;
	int		**res;
	char	**tmp;
	int		ind;

	len = ft_lstlen(lines);
	if (len <= 2)
		return (NULL);
	if (!(res = (int**)malloc(sizeof(int*) * (len))))
		return (NULL);
	ft_initialize_vars(&ind, &len, res);
	while (lines->next)
	{
		tmp = ft_strsplit((char*)lines->content, ' ');
		len = ft_strstrlen(tmp);
		if ((!tmp[0] && lines->next) || len < 2)
			return (NULL);
		if (!(res[ind] = ft_atoistr(tmp, ft_strstrlen(tmp))))
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
	char	**l;
	t_list	*lines;
	t_list	*l_end;

	lines = NULL;
	l_end = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0 || !(l = (char**)malloc(sizeof(char*))))
		return (NULL);
	while ((res = get_next_line(fd, l)) > 0)
	{
		ft_lstaddend(&l_end, ft_lstnew(*l, sizeof(char) * (ft_strlen(*l) + 1)));
		if (!lines)
			lines = l_end;
	}
	if (res < 0)
		return (NULL);
	if (lines)
		ft_lstaddend(&l_end, ft_lstnew(*l, sizeof(char) * (ft_strlen(*l) + 1)));
	if (!lines)
		lines = l_end;
	return (ft_lst_to_int_array(lines));
}
