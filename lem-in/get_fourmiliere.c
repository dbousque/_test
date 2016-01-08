/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fourmiliere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 12:28:37 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 15:20:38 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_fourmi *new_fourmi(int *path, int path_len)
{
	static int	id = 1;
	t_fourmi	*res;

	if (!(res = (t_fourmi*)malloc(sizeof(t_fourmi))))
		return (NULL);
	res->path = path;
	res->id = id;
	res->current_salle = path_len - 1;
	id++;
	return (res);
}

t_salle	*new_salle(char *name, int x_coord, int y_coord)
{
	static int	id = 0;
	t_salle		*res;

	if (!(res = (t_salle*)malloc(sizeof(t_salle))))
		return (NULL);
	res->x_coord = x_coord;
	res->y_coord = y_coord;
	res->accessible_salles = NULL;
	res->tmp_accessible_salles = NULL;
	res->tmp_accessible_salles_end = NULL;
	res->name = ft_strdup(name);
	res->id = id;
	id++;
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

char	only_numbers(char *str)
{
	int		i;

	if (ft_strlen(str) < 1)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

char	free_parts_n_return(char **parts, char return_value)
{
	int		i;
	int		len;

	i = 0;
	len = strstrlen(parts);
	while (i < len)
	{
		free(parts[i]);
		parts[i] = NULL;
		i++;
	}
	free(parts);
	parts = NULL;
	return (return_value);
}

char	is_input_correct(char *line)
{
	char	**parts;

	if (line[0] == '#')
		return (1);
	if (line[0] == 'L')
		return (0);
	if (ft_strlen(line) < 5)
		return (0);
	if (!(parts = ft_strsplit(line, ' ')))
		return (-1);
	if (strstrlen(parts) != 3 || !only_numbers(parts[1])
		|| !only_numbers(parts[2]))
		return (free_parts_n_return(parts, 0));
	return (free_parts_n_return(parts, 1));
}

char	is_start_or_end_salle(char **line, t_salle **start_salle,
									t_salle **end_salle, t_list **lines_end)
{
	char	start_end;

	start_end = 0;
	if ((*line)[0] == '#')
	{
		if ((*line)[1] != '#')
			return (-2);
		if ((*line)[2] && ft_strcmp(*line + 2, "start") == 0)
			start_end = 1;
		else if ((*line)[2] && ft_strcmp(*line + 2, "end") == 0)
			start_end = 2;
		else
			return (-2);
		if ((*start_salle && start_end == 1) || (*end_salle && start_end == 2))
			return (-1);
		ft_lstaddend(lines_end,
					ft_lstnew(*line, sizeof(char) * (ft_strlen(*line) + 1)));
		free(*line);
		if (get_next_line(0, line) == -1)
			return (-1);
		if (is_input_correct(*line) != 1 || !(*line) || ft_strlen(*line) <= 0)
			return (-1);
	}
	return (start_end);
}

char	free_parts_n_salle(char **parts, t_salle **salle, char return_val)
{
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	free(parts);
	free(*salle);
	*salle = NULL;
	return (return_val);
}

char	add_to_salles(t_list **salles_end, char **line,
							t_salle **str_end[2], t_list **lines_end)
{
	char	**parts;
	char	start_end;
	t_salle	*salle;

	start_end = is_start_or_end_salle(line, str_end[0], str_end[1], lines_end);
	if (start_end == -1)
		return (0);
	else if (start_end == -2)
		return (1);
	if (!(parts = ft_strsplit(*line, ' ')))
		return (0);
	if (!(salle = new_salle(parts[0], ft_atoi(parts[1]), ft_atoi(parts[2]))))
		return (0);
	ft_lstaddend(salles_end, ft_lstnew(salle, sizeof(t_salle)));
	if (start_end == 1)
		*str_end[0] = (t_salle*)((*salles_end)->content);
	else if (start_end == 2)
		*str_end[1] = (t_salle*)((*salles_end)->content);
	return (free_parts_n_salle(parts, &salle, 1));
}

t_salle	**list_to_salles(t_list *salles)
{
	t_salle	**res;
	t_list	*tmp;
	int		length;

	tmp = salles;
	length = 0;
	while (tmp)
	{
		length++;
		tmp = tmp->next;
	}
	if (!(res = (t_salle**)malloc(sizeof(t_salle*) * (length + 1))))
		return (NULL);
	res[length] = NULL;
	length = 0;
	tmp = salles;
	while (tmp)
	{
		res[length] = (t_salle*)tmp->content;
		length++;
		salles = tmp;
		tmp = tmp->next;
		free(salles);
	}
	return (res);
}

char	is_tube_description(char *line)
{
	char	**parts;
	int		i;

	if (ft_strlen(line) < 3)
		return (0);
	if (!(parts = ft_strsplit(line, '-')) || strstrlen(parts) != 2)
	{
		i = 0;
		while (parts[i])
		{
			free(parts[i]);
			i++;
		}
		free(parts);
		return (0);
	}
	free(parts[0]);
	free(parts[1]);
	free(parts);
	return (1);
}

char	salle_name_already_used(t_list *salles, t_salle *salle)
{
	while (salles && salles->next)
	{
		if (ft_strcmp(((t_salle*)salles->content)->name, salle->name) == 0)
			return (1);
		salles = salles->next;
	}
	return (0);
}

char	is_comment(char *line)
{
	if (line[0] != '#')
		return (0);
	return (1);
}

t_salle	**free_n_return_null(t_list *salles_end)
{
	free(((t_salle*)salles_end->content)->name);
	free(((t_salle*)salles_end->content));
	free(salles_end);
	salles_end = NULL;
	return (NULL);
}

t_salle	**not_valid_or_list_to_salles(char **line, t_list *salles)
{
	if (is_input_correct(*line) == -1
		|| (!is_tube_description(*line) && !is_comment(*line)))
	{
		free(*line);
		return (NULL);
	}
	return (list_to_salles(salles));
}

t_salle	**parse_salles(t_salle **start_salle, t_salle **end_salle,
												char **line, t_list **lines_end)
{
	t_list	*salles;
	t_list	*salles_end;
	t_salle	**start_end[2];

	salles = NULL;
	salles_end = NULL;
	if (get_next_line(0, line) == -1)
		return (NULL);
	start_end[0] = start_salle;
	start_end[1] = end_salle;
	while (is_input_correct(*line) == 1 && line && ft_strlen(*line) > 0)
	{
		if (!(add_to_salles(&salles_end, line, start_end, lines_end)))
			return (NULL);
		if (!salles)
			salles = salles_end;
		if (salle_name_already_used(salles, (t_salle*)salles_end->content))
			return (free_n_return_null(salles_end));
		ft_lstaddend(lines_end,
				ft_lstnew(*line, sizeof(char) * (ft_strlen(*line) + 1)));
		free(*line);
		if (get_next_line(0, line) == -1)
			return (NULL);
	}
	return (not_valid_or_list_to_salles(line, salles));
}

void	put_salle(t_salle *salle)
{
	int		i;

	ft_printf("SALLE N %d :\n  - NAME : %s\n  - X : %d\n  - Y : %d\n",
			salle->id, salle->name, salle->x_coord, salle->y_coord);
	i = 0;
	while (salle->accessible_salles && salle->accessible_salles[i])
	{
		ft_printf("     access : %d\n", salle->accessible_salles[i]->id);
		i++;
	}
}

void	put_salles(t_salle **salles)
{
	int		i;

	i = 0;
	while (salles[i])
	{
		put_salle(salles[i]);
		i++;
	}
}

t_salle	*get_salle_by_name(t_salle **salles, char *name)
{
	int		i;

	i = 0;
	while (salles[i])
	{
		if (ft_strcmp(salles[i]->name, name) == 0)
			return (salles[i]);
		i++;
	}
	return (NULL);
}

int		add_tube_from_to(t_salle *from, t_salle *to)
{
	t_list	*new;

	if (!(new = ft_lstnew(&to, sizeof(t_salle**))))
		return (0);
	ft_lstaddend(&(from->tmp_accessible_salles_end), new);
	if (!(from->tmp_accessible_salles))
		from->tmp_accessible_salles = from->tmp_accessible_salles_end;
	return (1);
}

int		add_tubes(t_salle **salles, char *line)
{
	char	**parts;
	t_salle	*first;
	t_salle	*second;

	if (!(parts = ft_strsplit(line, '-')))
		return (0);
	if (!(first = get_salle_by_name(salles, parts[0])))
		return (0);
	if (!(second = get_salle_by_name(salles, parts[1])))
		return (0);
	if (first == second)
		return (0);
	if (!(add_tube_from_to(first, second)))
		return (0);
	if (!(add_tube_from_to(second, first)))
		return (0);
	return (1);
}

int		get_tubes(t_salle **salles, char *line, t_list **lines_end)
{
	while (is_tube_description(line) || is_comment(line))
	{
		ft_lstaddend(lines_end,
				ft_lstnew(line, sizeof(char) * (ft_strlen(line) + 1)));
		if (!is_comment(line))
		{
			if (!(add_tubes(salles, line)))
				return (0);
		}
		free(line);
		if (get_next_line(0, &line) == -1)
			return (0);
	}
	free(line);
	return (1);
}

int		listlen(t_list *list)
{
	int		length;

	length = 0;
	while (list)
	{
		length++;
		list = list->next;
	}
	return (length);
}

int		accessible_list_to_array(t_salle **salles)
{
	t_list	*tmp;
	int		i;
	int		len;
	int		x;

	i = 0;
	while (salles[i])
	{
		tmp = salles[i]->tmp_accessible_salles;
		len = listlen(tmp);
		if (!(salles[i]->accessible_salles = (t_salle**)malloc(sizeof(t_salle*)
														* (len + 1))))
			return (0);
		salles[i]->accessible_salles[len] = NULL;
		x = 0;
		while (tmp)
		{
			salles[i]->accessible_salles[x] = *((t_salle**)tmp->content);
			tmp = tmp->next;
			x++;
		}
		i++;
	}
	return (1);
}

void	free_tmp_lists(t_salle **salles)
{
	int		i;
	t_list	*tmp;
	t_list	*tmp2;

	i = 0;
	while (salles[i])
	{
		tmp = salles[i]->tmp_accessible_salles;
		while (tmp)
		{
			tmp2 = tmp->next;
			free(tmp);
			tmp = NULL;
			tmp = tmp2;
		}
		salles[i]->tmp_accessible_salles = NULL;
		salles[i]->tmp_accessible_salles_end = NULL;
		i++;
	}
}

t_fourm	*salles_to_fourmiliere(int nb_fourmis, t_salle **salles,
								t_salle *start_salle, t_salle *end_salle)
{
	t_fourm	*res;

	if (!(res = (t_fourm*)malloc(sizeof(t_fourm))))
		return (NULL);
	res->nb_fourmis = nb_fourmis;
	res->salles = salles;
	res->start = start_salle;
	res->end = end_salle;
	return (res);
}

t_fourm	*get_fourmiliere(t_salle **start_salle, t_salle **end_salle,
																t_list **lines)
{
	t_salle	**salles;
	char	*line;
	int		nb_fourm;
	t_list	*lines_end;

	if (get_next_line(0, &line) == -1 || !only_numbers(line) || line[0] == '0')
		return (NULL);
	nb_fourm = ft_atoi(line);
	lines_end = NULL;
	ft_lstaddend(&lines_end,
			ft_lstnew(line, sizeof(char) * (ft_strlen(line) + 1)));
	*lines = lines_end;
	free(line);
	salles = parse_salles(start_salle, end_salle, &line, &lines_end);
	if (!salles)
		return (NULL);
	if (!(*start_salle) || !(*end_salle))
		return (NULL);
	if (!(get_tubes(salles, line, &lines_end)))
		return (NULL);
	if (!(accessible_list_to_array(salles)))
		return (NULL);
	free_tmp_lists(salles);
	put_salles(salles);
	return (salles_to_fourmiliere(nb_fourm, salles, *start_salle, *end_salle));
}

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
	int		not_found;
	t_salle	*salle;

	salle = fourm->salles[*((int*)path->content)];
	i = 0;
	while (salle->accessible_salles[i])
	{
		tmp = path;
		not_found = 1;
		while (tmp && not_found)
		{
			if (*(int*)(tmp->content) == salle->accessible_salles[i]->id)
				not_found = 0;
			tmp = tmp->next;
		}
		if (not_found)
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

int		add_step_to_paths(t_list **paths, t_list **paths_end,
	t_list **finished_paths, t_list **finished_paths_end, t_fourm *fourmiliere)
{
	t_list	*tmp;
	t_list	*tmp2;
	int		len;

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

int		**find_best_paths(t_fourm *fourmiliere, int nb_paths, t_list **finished_paths)
{
	int		**res;
	int		current_path_length;
	t_list	*paths;
	t_list	*paths_end;
	t_list	*finished_paths_end;

	if (!(paths = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!(paths->content = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	paths->next = NULL;
	((t_list*)paths->content)->content = &fourmiliere->start->id;
	((t_list*)paths->content)->next = NULL;
	current_path_length = 0;
	//free((int*)paths_end->content);
	//free(paths_end);
	paths_end = paths;
	*finished_paths = NULL;
	finished_paths_end = NULL;
	while (!(res = find_suitable_paths(*finished_paths, nb_paths, fourmiliere)) && paths)
	{
		if (!(add_step_to_paths(&paths, &paths_end, finished_paths, &finished_paths_end, fourmiliere)))
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
		ft_printf("L%d-%s", tmp_fourmi->id, fourmiliere->salles[tmp_fourmi->path[tmp_fourmi->current_salle]]->name);
		if (fourmis->next)
			ft_putchar(' ');
		fourmis = fourmis->next;
	}
	ft_putchar('\n');
}

void	remove_fourmis_at_end(t_list **fourmis, t_list **fourmis_end)
{
	t_list	*tmp;
	t_list	*parent;
	t_list	*next;

	tmp = *fourmis;
	parent = NULL;
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

int		make_fourmis_travel(int **best_paths, t_fourm *fourmiliere)
{
	int		i;
	int		nb_paths;
	int		*paths_len;
	t_list	*fourmis;
	t_list	*fourmis_end;
	char	go_on;

	ft_putchar('\n');
	nb_paths = intintlen(best_paths);
	if (!(paths_len = get_paths_len(best_paths, nb_paths)))
		return (ft_error());
	fourmis = NULL;
	fourmis_end = NULL;
	while (fourmiliere->nb_fourmis > 0 || fourmis)
	{
		make_turn(fourmis);
		if (fourmiliere->nb_fourmis > 0)
		{
			ft_lstaddend(&fourmis_end, ft_lstnew(new_fourmi(best_paths[0], paths_len[0]), sizeof(t_fourmi)));
			fourmiliere->nb_fourmis--;
			if (!fourmis)
				fourmis = fourmis_end;
			i = 1;
			go_on = 1;
			while (go_on && best_paths[i] && fourmiliere->nb_fourmis > 0)
			{
			//	if (turns_required_for_n_fourmis(paths_len[i], 1) <= turns_required_for_n_fourmis(paths_len[i - 1], fourmiliere->nb_fourmis / (nb_paths - 1)))
			if (turns_required_for_n_fourmis(paths_len[i], 1) <= turns_required_for_n_fourmis(paths_len[i - 1], fourmiliere->nb_fourmis / i))
				{
					ft_lstaddend(&fourmis_end, ft_lstnew(new_fourmi(best_paths[i], paths_len[i]), sizeof(t_fourmi)));
					fourmiliere->nb_fourmis--;
				}
				else
					go_on = 0;
				i++;
			}
		}
		remove_fourmis_at_end(&fourmis, &fourmis_end);
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

int		main(void)
{
	t_fourm	*fourmiliere;
	t_salle	*start_salle;
	t_salle	*end_salle;
	int		nb_paths_to_find;
	int		**best_paths;
	t_list	*finished_paths;
	t_list	*lines;

	start_salle = NULL;
	end_salle = NULL;
	if (!(fourmiliere = get_fourmiliere(&start_salle, &end_salle, &lines)))
		return (ft_error());
	if (!(nb_paths_to_find = min_end_start(fourmiliere)))
		return (ft_error());
	if (!(best_paths = find_best_paths(fourmiliere, nb_paths_to_find, &finished_paths)))
	{
		nb_paths_to_find--;
		while (nb_paths_to_find > 0 && !(best_paths = find_suitable_paths(finished_paths, nb_paths_to_find, fourmiliere)))
			nb_paths_to_find--;
		if (!best_paths)
			return (ft_error());
	}
	put_lines(lines);
	put_best_paths(best_paths);
	return (make_fourmis_travel(best_paths, fourmiliere));
}
