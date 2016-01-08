/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 18:17:29 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 19:11:31 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*copy_list(t_list *path)
{
	t_list	*ints;
	t_list	*ints_end;
	t_list	*res;
	t_list	*tmp;

	ints = NULL;
	ints_end = NULL;
	tmp = path;
	while (tmp)
	{
		ft_lstaddend(&ints_end, ft_lstnew((int*)tmp->content, sizeof(int)));
		if (!ints)
			ints = ints_end;
		tmp = tmp->next;
	}
	ints_end->next = NULL;
	if (!(res = ft_lstnew(ints, sizeof(t_list*))))
		return (NULL);
	return (ints);
}

int		new_path(t_list *path, int *new_salle_id, t_list **paths_list_end)
{
	t_list	*new_list;

	if (!(new_list = copy_list(path)))
		return (0);
	ft_lstadd(&new_list, ft_lstnew(new_salle_id, sizeof(int)));
	ft_lstaddend(paths_list_end, ft_lstnew(new_list, sizeof(t_list)));
	return (1);
}

int		add_paths_from_salle(t_list *path, t_list **paths_end,
							t_list **fin_paths_end, t_fourm *fourm)
{
	int		i;
	t_list	*tmp;
	t_salle	*salle;

	salle = fourm->salles[*((int*)path->content)];
	i = 0;
	while (salle->accessible_salles[i])
	{
		tmp = path;
		while (tmp && *(int*)(tmp->content) != salle->accessible_salles[i]->id)
			tmp = tmp->next;
		if (!tmp)
		{
			if (!((salle->accessible_salles[i]->id == fourm->end->id)
			? new_path(path, &salle->accessible_salles[i]->id, fin_paths_end)
			: new_path(path, &salle->accessible_salles[i]->id, paths_end)))
				return (0);
		}
		i++;
	}
	return (1);
}

int		add_step_to_paths(t_list *paths_arg[2], t_list **finished_paths,
							t_list **finished_paths_end, t_fourm *fourmiliere)
{
	t_list	*tmp;
	t_list	*tmp2;
	int		len;
	t_list	**paths;
	t_list	**paths_end;

	paths = &paths_arg[0];
	paths_end = &paths_arg[1];
	len = listlen(*paths);
	tmp = *paths;
	while (tmp && len > 0)
	{
		if (!(add_paths_from_salle((t_list*)tmp->content, paths_end,
											finished_paths_end, fourmiliere)))
			return (0);
		if (!(*finished_paths) && *finished_paths_end)
			*finished_paths = *finished_paths_end;
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
		len--;
	}
	*paths = tmp;
	return (1);
}

int		**find_best_paths(t_fourm *fourm, int nb_paths, t_list **finished_paths)
{
	int		**res;
	int		current_path_length;
	t_list	*paths[2];
	t_list	*fini_paths_end;

	if (!(paths[0] = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!(paths[0]->content = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	paths[0]->next = NULL;
	((t_list*)paths[0]->content)->content = &fourm->start->id;
	((t_list*)paths[0]->content)->next = NULL;
	current_path_length = 0;
	paths[1] = paths[0];
	*finished_paths = NULL;
	fini_paths_end = NULL;
	while (!(res = find_suitable_paths(*finished_paths, nb_paths, fourm))
			&& paths[0])
	{
		if (!(add_step_to_paths(paths, finished_paths, &fini_paths_end, fourm)))
			return (NULL);
		current_path_length++;
	}
	return (res);
}
