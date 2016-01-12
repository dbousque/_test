/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 18:53:28 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/12 19:02:53 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_to_lists(int error, t_list **params, t_list **other_params,
													char *str, t_flags *flags)
{
	struct stat	*tmp_stat;

	if (!(tmp_stat = (struct stat*)malloc(sizeof(struct stat))))
		return ;
	lstat(str, tmp_stat);
	if (flags->l && get_d_type_from_stat(tmp_stat) != DT_DIR)
		error = ENOTDIR;
	if (error == -1)
	{
		if (!*params)
			ft_lstaddend(params,
						ft_lstnew(str, sizeof(char) * (ft_strlen(str) + 1)));
		else
			ft_lstadd(params,
						ft_lstnew(str, sizeof(char) * (ft_strlen(str) + 1)));
	}
	else if (error == ENOTDIR)
	{
		if (!*other_params)
			ft_lstaddend(other_params,
						ft_lstnew(str, sizeof(char) * (ft_strlen(str) + 1)));
		else
			ft_lstadd(other_params,
						ft_lstnew(str, sizeof(char) * (ft_strlen(str) + 1)));
	}
	else
		print_errno(error, str);
}

char	**get_params(int argc, char **argv, int i, t_list **other_params, t_flags *flags)
{
	t_list		*params;
	DIR			*tmp;
	int			error;
	struct stat	*stats;

	params = NULL;
	if (!(stats = (struct stat*)malloc(sizeof(struct stat))))
		return (NULL);
	if (i == argc)
		ft_lstaddend(&params, ft_lstnew(".", sizeof(char) * 2));
	else
	{
		while (i < argc)
		{
			error = -1;
			if (!(tmp = opendir(argv[i])))
			{
				error = errno;
				if (error == ENOENT && !(lstat(argv[i], stats)))
					error = ENOTDIR;
				if (error != ENOTDIR)
					print_errno(error, argv[i]);
			}
			if (error == -1 || error == ENOTDIR)
			{
				if (error == -1 && closedir(tmp) == -1)
					error = errno;
				add_to_lists(error, &params, other_params, argv[i], flags);
			}
			i++;
		}
	}
	return (list_to_string_array(params));
}
