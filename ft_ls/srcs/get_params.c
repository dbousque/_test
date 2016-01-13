/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 18:53:28 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/13 16:40:17 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_to_lists(int error, t_list ***params, char *str, t_flags *flags)
{
	struct stat	*tmp_stat;

	if (!(tmp_stat = (struct stat*)malloc(sizeof(struct stat))))
		return ;
	lstat(str, tmp_stat);
	if (flags->l && get_d_type_from_stat(tmp_stat) != DT_DIR)
		error = ENOTDIR;
	if (error == -1 && !flags->d)
	{
		(!*params[0]) ? ft_lstaddend(params[0], ft_lstnew(str,
					sizeof(char) * (ft_strlen(str) + 1))) : ft_lstadd(params[0],
						ft_lstnew(str, sizeof(char) * (ft_strlen(str) + 1)));
	}
	else if (error == ENOTDIR || (error == -1 && flags->d))
	{
		if (!*params[1])
			ft_lstaddend(params[1],
						ft_lstnew(str, sizeof(char) * (ft_strlen(str) + 1)));
		else
			ft_lstadd(params[1],
						ft_lstnew(str, sizeof(char) * (ft_strlen(str) + 1)));
	}
	else
		print_errno(error, str);
}

void	nothing(int i)
{
	(void)i;
}

char	**multiple_params(char **argv, int argc, t_list **params[2],
																t_flags *flags)
{
	int			err;
	int			i;
	DIR			*tmp;
	struct stat	*stats;

	if (!(stats = (struct stat*)malloc(sizeof(struct stat))))
		return (NULL);
	i = 0;
	while (i < argc)
	{
		err = -1;
		if (!(tmp = opendir(argv[i])))
		{
			err = errno;
			err = (err == ENOENT && !(lstat(argv[i], stats))) ? ENOTDIR : err;
			(err != ENOTDIR) ? print_errno(err, argv[i]) : nothing(i);
		}
		if (err == -1 || err == ENOTDIR)
		{
			err = (err == -1 && closedir(tmp) == -1) ? errno : err;
			add_to_lists(err, params, argv[i], flags);
		}
		i++;
	}
	return (argv);
}

char	**get_params(int argc, char **argv, t_list **other_params,
																t_flags *flags)
{
	t_list		**params[2];

	params[0] = (t_list**)malloc(sizeof(t_list*));
	*params[0] = NULL;
	params[1] = other_params;
	if (argc == 0 && !flags->d)
		ft_lstaddend(params[0], ft_lstnew(".", sizeof(char) * 2));
	else if (argc == 0 && flags->d)
		ft_lstaddend(params[1], ft_lstnew(".", sizeof(char) * 2));
	else
	{
		if (!(multiple_params(argv, argc, params, flags)))
			return (NULL);
	}
	return (list_to_string_array(*params[0]));
}
