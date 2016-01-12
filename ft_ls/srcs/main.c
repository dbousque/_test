/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 13:59:24 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/12 19:36:17 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

struct dirent	**strstr_to_dirent_array(char **params, int *l)
{
	struct dirent	**children;
	int				i;

	*l = 0;
	while (params[*l])
		(*l)++;
	if (*l <= 0)
		return (NULL);
	if (!(children = (struct dirent**)malloc(sizeof(struct dirent*)
																* (*l + 1))))
		return (unexpected_error_null());
	i = 0;
	while (i < *l)
	{
		if (!(children[i] = (struct dirent*)malloc(sizeof(struct dirent))))
			return (unexpected_error_null());
		ft_strcpy(children[i]->d_name, params[i]);
		i++;
	}
	return (children);
}

int				ft_strcmp_void(void *elt1, void *elt2, void *elt3)
{
	(void)elt3;
	return (-ft_strcmp((char*)elt1, (char*)elt2));
}

void			sort_args(int argc, char **argv, int i)
{
	if (argc - i <= 1)
		return ;
	if (argc - i < 400)
		quicksort((void**)(argv + i), argc - i, ft_strcmp_void, NULL);
	else
		insertion_sort((void**)(argv + i), argc - i, ft_strcmp_void, NULL);
}

int				found_void_param(int argc, char **argv, int i)
{
	while (i < argc)
	{
		if (ft_strlen(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_flags			*flags;
	char			**dir_params;
	char			**other_params;
	t_list			**other_params_list;
	int				i;

	if (!(other_params_list = (t_list**)malloc(sizeof(t_list*))))
		return (unexpected_error());
	*other_params_list = NULL;
	other_params = NULL;
	if (!(flags = get_flags(argc, argv, &i)))
		return (0);
	if (found_void_param(argc, argv, i))
	{
		print_errno(ENOENT, "");
		return (0);
	}
	sort_args(argc, argv, i);
	argv += i;
	argc -= i;
	dir_params = get_params(argc, argv, other_params_list, flags);
	if (other_params_list)
		other_params = list_to_string_array(*other_params_list);
	return (print_params(dir_params, other_params, flags, argc));
}
