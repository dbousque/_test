/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 18:32:53 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/12 19:35:15 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

__uint8_t	get_d_type_from_stat(struct stat *stats)
{
	if (stats->st_mode & S_IFIFO)
		return (DT_FIFO);
	if (stats->st_mode & S_IFDIR)
		return (DT_DIR);
	if (stats->st_mode & S_IFREG)
		return (DT_REG);
	if (stats->st_mode & S_IFLNK)
		return (DT_LNK);
	if (stats->st_mode & S_IFCHR)
		return (DT_CHR);
	if (stats->st_mode & S_IFBLK)
		return (DT_BLK);
	if (stats->st_mode & S_IFSOCK)
		return (DT_SOCK);
	if (stats->st_mode & S_IFWHT)
		return (DT_WHT);
	return (DT_UNKNOWN);
}

char		*make_path(char *filename, char *dir_name)
{
	int		len;

	if (!dir_name)
		return (filename);
	len = ft_strlen(dir_name);
	if (dir_name[len - 1] != '/')
		dir_name = ft_strjoin(dir_name, "/");
	return (ft_strjoin(dir_name, filename));
}

char		**list_to_string_array(t_list *params)
{
	int		length;
	t_list	*tmp;
	char	**res;

	tmp = params;
	length = 0;
	while (tmp)
	{
		tmp = tmp->next;
		length++;
	}
	if (!(res = (char**)malloc(sizeof(char*) * (length + 1))))
		return (NULL);
	res[length] = NULL;
	length = 0;
	while (params)
	{
		res[length] = (char*)params->content;
		tmp = params;
		params = params->next;
		free(tmp);
		length++;
	}
	return (res);
}

int		strstrlen(char **strstr)
{
	int		i;

	i = 0;
	while (strstr[i])
		i++;
	return (i);
}
