/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:39:07 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 17:39:10 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*match(char *start, t_linked_list *candidates)
{
	int		i;
	size_t	x;
	char	*cand;
	int		count;

	count = 0;
	i = 0;
	while (i < candidates->len)
	{
		x = 0;
		while (start[x] && ((char*)candidates->elts[i])[x]
			&& start[x] == ((char*)candidates->elts[i])[x])
			x++;
		if (!start[x])
		{
			cand = candidates->elts[i];
			count++;
		}
		i++;
	}
	if (count != 1)
		return (NULL);
	return (ft_strdup(cand));
}

char	*get_end(char *start, int *nb_removed)
{
	int		i;

	if (!char_in_str(start, '/'))
	{
		*nb_removed = 0;
		return (start);
	}
	i = ft_strlen(start);
	i--;
	while (i >= 0)
	{
		if (start[i] == '/')
		{
			*nb_removed = i + 1;
			return (start + i + 1);
		}
		i--;
	}
	*nb_removed = 0;
	return (start);
}

char	*rebuild_res(char *res, char *line, int nb_removed)
{
	size_t	len;
	int		i;
	char	*final;

	len = ft_strlen(res) + nb_removed;
	if (!(final = (char*)malloc(sizeof(char) * (len + 1))))
		malloc_error();
	final[len] = '\0';
	i = 0;
	while (i < nb_removed)
	{
		final[i] = line[i];
		i++;
	}
	while (res[i - nb_removed])
	{
		final[i] = res[i - nb_removed];
		i++;
	}
	return (final);
}

void	look_for_matching_file(char *start, t_linked_list *candidates)
{
	char	*tmp_dir;

	if (char_in_str(start, '/'))
	{
		tmp_dir = get_dir_name(start);
		get_files_in_dir(tmp_dir, candidates, 1, 1);
		free(tmp_dir);
	}
	else
		get_files_in_dir("./", candidates, 1, 1);
}

size_t	get_len(char **parts)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (parts[i] && parts[i + 1])
	{
		len += ft_strlen(parts[i]) + 1;
		i++;
	}
	return (len);
}
