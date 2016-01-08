/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fourmiliere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 12:28:37 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 17:02:56 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		min_end_start(t_fourm *fourmiliere)
{
	int		len_start;
	int		len_end;

	len_start = 0;
	while (fourmiliere->start->accessible_salles[len_start])
		len_start++;
	len_end = 0;
	while (fourmiliere->end->accessible_salles[len_end])
		len_end++;
	if (len_end < len_start)
		return (len_end);
	return (len_start);
}

char	no_shared_salle(t_list *tmp, t_list *visited_salles)
{
	t_list	*tmp2;

	while (tmp)
	{
		tmp2 = visited_salles;
		while (tmp2)
		{
			if (*((int*)tmp->content) == *((int*)tmp2->content))
				return (0);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

void	add_salles_to_visited(t_list *path, t_list **visited_salles,
							t_list **visited_salles_end, t_fourm *fourmiliere)
{
	t_list	*tmp;

	tmp = path;
	while (tmp)
	{
		if (*(int*)tmp->content != fourmiliere->end->id
			&& *(int*)tmp->content != fourmiliere->start->id)
		{
			ft_lstaddend(visited_salles_end,
									ft_lstnew((int*)tmp->content, sizeof(int)));
			if (!*visited_salles)
				*visited_salles = *visited_salles_end;
		}
		tmp = tmp->next;
	}
}

int		**path_to_int_paths(t_list **best_paths, int nb_paths)
{
	int		**res;
	t_list	*tmp;
	int		x;
	int		i;

	if (!(res = (int**)malloc(sizeof(int*) * (nb_paths + 1))))
		return (NULL);
	res[nb_paths] = NULL;
	i = 0;
	while (i < nb_paths)
	{
		if (!(res[i] = (int*)malloc(sizeof(int) * listlen(best_paths[i]))))
			return (NULL);
		x = 0;
		tmp = best_paths[i];
		while (tmp)
		{
			res[i][x] = *((int*)tmp->content);
			x++;
			tmp = tmp->next;
		}
		i++;
	}
	return (res);
}

void	put_path(t_list *path)
{
	while (path)
	{
		ft_putnbr(*(int*)path->content);
		ft_putstr(", ");
		path = path->next;
	}
	ft_putchar('\n');
}

void	put_paths(t_list *paths)
{
	while (paths)
	{
		put_path((t_list*)paths->content);
		paths = paths->next;
	}
}

int		turns_required_for_n_fourmis(int path_len, int nb_fourmis)
{
	int		res;

	res = nb_fourmis - 1 + (path_len - 1);
	return (res);
}

/*
** adding_path_will_make_way_longer
*/

char	lon(t_list **best_paths, int nb_best, int current_path_len,
																int nb_fourmis)
{
	int		steps_witho;
	int		steps_with;

	steps_witho = turns_required_for_n_fourmis(listlen(best_paths[nb_best - 1]),
														nb_fourmis / nb_best);
	steps_with = turns_required_for_n_fourmis(current_path_len, 1);
	if (steps_witho <= steps_with)
		return (1);
	return (0);
}

void	init_vars(t_list *visited[2], t_list **best_paths,
											t_list *finished_paths, int *len)
{
	*len = listlen(finished_paths);
	best_paths[0] = (t_list*)finished_paths->content;
	visited[0] = NULL;
	visited[1] = NULL;
}

int		**test_paths_from_i(int x, t_list *finished_paths, t_fourm *four,
																int nb_paths)
{
	t_list	*best_pat[nb_paths];
	t_list	*visited[2];
	t_list	*tmp;
	int		len;
	int		nb;

	init_vars(visited, best_pat, finished_paths, &len);
	nb = 1;
	tmp = finished_paths->next;
	add_salles_to_visited(best_pat[0], &visited[0], &visited[1], four);
	while (++x < len)
	{
		if (lon(best_pat, nb, listlen((t_list*)tmp->content), four->nb_fourmis))
			return (path_to_int_paths(best_pat, nb));
		if (no_shared_salle((t_list*)tmp->content, visited[0]))
		{
			best_pat[nb] = (t_list*)tmp->content;
			add_salles_to_visited(best_pat[nb], &visited[0], &visited[1], four);
			nb++;
		}
		if (nb == nb_paths)
			return (path_to_int_paths(best_pat, nb_paths));
		tmp = tmp->next;
	}
	return (NULL);
}

int		**find_suitable_paths(t_list *finished_paths, int nb_paths,
														t_fourm *fourmiliere)
{
	int		i;
	int		len;
	int		**res;

	if (!finished_paths)
		return (NULL);
	len = listlen(finished_paths);
	if (nb_paths == 1)
		return (path_to_int_paths((t_list**)&(finished_paths->content), 1));
	i = 0;
	while (i <= len - nb_paths)
	{
		if ((res = test_paths_from_i(i, finished_paths, fourmiliere,
																	nb_paths)))
			return (res);
		finished_paths = finished_paths->next;
		i++;
	}
	return (NULL);
}

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
	put_paths(*finished_paths);
	return (res);
}

void	put_best_paths(int **best_paths)
{
	int		i;
	int		x;

	i = 0;
	ft_putendl("BEST PATHS :");
	while (best_paths[i])
	{
		x = 0;
		while (best_paths[i][x])
		{
			ft_putnbr(best_paths[i][x]);
			ft_putstr(", ");
			x++;
		}
		i++;
		ft_putchar('\n');
	}
}

int		intintlen(int **intint)
{
	int		i;

	i = 0;
	while (intint[i])
		i++;
	return (i);
}

int		int_tab_len(int *tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		*get_paths_len(int **best_paths, int nb_paths)
{
	int		i;
	int		*res;

	if (!(res = (int*)malloc(sizeof(int) * (nb_paths + 1))))
		return (NULL);
	res[nb_paths] = 0;
	i = 0;
	while (i < nb_paths)
	{
		res[i] = int_tab_len(best_paths[i]);
		i++;
	}
	return (res);
}

void	make_turn(t_list *fourmis)
{
	t_fourmi	*tmp_fourmi;

	while (fourmis)
	{
		tmp_fourmi = ((t_fourmi*)fourmis->content);
		tmp_fourmi->current_salle--;
		fourmis = fourmis->next;
	}
}

void	print_fourmis(t_list *fourmis, t_fourm *fourmiliere)
{
	t_fourmi	*tmp_fourmi;

	while (fourmis)
	{
		tmp_fourmi = ((t_fourmi*)fourmis->content);
		ft_printf("L%d-%s", tmp_fourmi->id,
		fourmiliere->salles[tmp_fourmi->path[tmp_fourmi->current_salle]]->name);
		if (fourmis->next)
			ft_putchar(' ');
		fourmis = fourmis->next;
	}
	ft_putchar('\n');
}

void	remove_fourmis_at_end(t_list **fourmis, t_list **fourmis_end,
																t_list *parent)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *fourmis;
	while (tmp)
	{
		if (((t_fourmi*)tmp->content)->current_salle <= -1)
		{
			next = tmp->next;
			free(tmp);
			if (!parent)
				*fourmis = next;
			else
				parent->next = next;
			if (!next)
				*fourmis_end = parent;
			tmp = next;
		}
		else
		{
			parent = tmp;
			tmp = tmp->next;
		}
	}
}

int		ft_error(void)
{
	ft_putendl_fd("ERROR", 2);
	return (0);
}

void	fourm_on_ot_paths(int **best_paths, int *paths_len,
								t_fourm *fourmiliere, t_list **fourmis_end)
{
	char	go_on;
	int		i;

	i = 1;
	go_on = 1;
	while (go_on && best_paths[i] && fourmiliere->nb_fourmis > 0)
	{
		if (turns_required_for_n_fourmis(paths_len[i], 1) <=
	turns_required_for_n_fourmis(paths_len[i - 1], fourmiliere->nb_fourmis / i))
		{
			ft_lstaddend(fourmis_end,
				ft_lstnew(
					new_fourmi(best_paths[i], paths_len[i]), sizeof(t_fourmi)));
			fourmiliere->nb_fourmis--;
		}
		else
			go_on = 0;
		i++;
	}
}

int		make_fourmi_travel(int **best_paths, t_fourm *fourmiliere, int nb_paths,
															t_list *fourmis_end)
{
	int		*paths_len;
	t_list	*fourmis;

	ft_putchar('\n');
	if (!(paths_len = get_paths_len(best_paths, nb_paths)))
		return (ft_error());
	fourmis = NULL;
	while (fourmiliere->nb_fourmis > 0 || fourmis)
	{
		make_turn(fourmis);
		if (fourmiliere->nb_fourmis > 0)
		{
			ft_lstaddend(&fourmis_end, ft_lstnew(
					new_fourmi(best_paths[0], paths_len[0]), sizeof(t_fourmi)));
			fourmiliere->nb_fourmis--;
			if (!fourmis)
				fourmis = fourmis_end;
			fourm_on_ot_paths(best_paths, paths_len, fourmiliere, &fourmis_end);
		}
		remove_fourmis_at_end(&fourmis, &fourmis_end, NULL);
		if (fourmis)
			print_fourmis(fourmis, fourmiliere);
	}
	return (0);
}

void	put_lines(t_list *lines)
{
	while (lines)
	{
		ft_putendl((char*)lines->content);
		lines = lines->next;
	}
}

int		find_best_paths_and_travel(t_fourm *fourmiliere, t_list *lines,
																int nb_paths)
{
	int		**best_paths;
	t_list	*finished_paths;

	if (!(best_paths = find_best_paths(fourmiliere, nb_paths, &finished_paths)))
	{
		nb_paths--;
		while (nb_paths > 0 && !(best_paths =
			find_suitable_paths(finished_paths, nb_paths, fourmiliere)))
			nb_paths--;
		if (!best_paths)
			return (ft_error());
	}
	put_lines(lines);
	put_best_paths(best_paths);
	return (make_fourmi_travel(best_paths, fourmiliere, intintlen(best_paths),
																		NULL));
}

int		main(void)
{
	t_fourm	*fourmiliere;
	t_salle	*start_salle;
	t_salle	*end_salle;
	int		nb_paths_to_find;
	t_list	*lines;

	start_salle = NULL;
	end_salle = NULL;
	if (!(fourmiliere = get_fourmiliere(&start_salle, &end_salle, &lines)))
		return (ft_error());
	if (!(nb_paths_to_find = min_end_start(fourmiliere)))
		return (ft_error());
	return (find_best_paths_and_travel(fourmiliere, lines, nb_paths_to_find));
}
