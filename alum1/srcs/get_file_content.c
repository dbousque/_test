/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 22:06:26 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/20 17:12:33 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alum1.h"

int		list_to_array(t_list *content, char ***file)
{
	int		nb;
	t_list	*tmp;
	int		ind;

	tmp = content;
	nb = 0;
	while (tmp)
	{
		nb++;
		tmp = tmp->next;
	}
	if (!(*file = (char**)malloc(sizeof(char*) * (nb + 1))))
		return (-2);
	(*file)[nb] = NULL;
	tmp = content;
	ind = 0;
	while (tmp)
	{
		if (!((*file)[ind] = ft_strdup(tmp->content)))
			return (-2);
		ind++;
		tmp = tmp->next;
	}
	return (0);
}

int		get_file_content(char *filename, char stdinp, char ***file, char goon)
{
	int		fd;
	t_list	*content;
	t_list	*content_end;
	int		re;
	char	**line;

	fd = ((!stdinp && filename) ? open(filename, O_RDONLY) : 0);
	if (!filename || fd < 0 || !(line = (char**)malloc(sizeof(char*))))
		return (-2);
	content = NULL;
	content_end = NULL;
	re = 1;
	while (goon && ((re == 1 && (re = get_next_line(fd, line)) == 0) || re > 0))
	{
		if (!line)
			return (-2);
		ft_lstaddend(&content_end, ft_lstnew(*line, ft_strlen(*line) + 1));
		if (!content)
			content = content_end;
		goon = ((fd == 0 && !(*line && (*line)[0])) ? 0 : 1);
	}
	if (fd != 0)
		close(fd);
	return (list_to_array(content, file));
}
