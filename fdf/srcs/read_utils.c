/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 17:36:46 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/17 17:38:22 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
