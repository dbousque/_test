/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:39:14 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 17:39:16 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	look_for_matching_exec(char *start, t_linked_list *candidates,
																char **env)
{
	char	*tmp_dir;

	if (char_in_str(start, '/'))
	{
		tmp_dir = get_dir_name(start);
		get_files_in_dir(tmp_dir, candidates, 1, 0);
		free(tmp_dir);
	}
	else
		get_files_from_path2(env, candidates);
}

void	look_for_matching_dir(char *start, t_linked_list *candidates)
{
	char	*tmp_dir;

	if (char_in_str(start, '/'))
	{
		tmp_dir = get_dir_name(start);
		get_files_in_dir(tmp_dir, candidates, 2, 1);
		free(tmp_dir);
	}
	else
		get_files_in_dir("./", candidates, 2, 1);
}
