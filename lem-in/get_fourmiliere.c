

#include "lem_in.h"

typedef struct		s_salle
{
	char			*name;
	struct s_salle	**accessible_salles;
	t_list			*tmp_accessible_salles;
	t_list			*tmp_accessible_salles_end;
	//t_fourmi		*fourmi;
	int				x_coord;
	int				y_coord;
	int				id;
}					t_salle;

typedef struct	s_fourm
{
	t_salle		**salles;
	int			nb_fourmis;
	t_salle		*start;
	t_salle		*end;
}				t_fourm;

t_salle	*new_salle(char *name, int x_coord, int y_coord)
{
	static int	id = 0;
	t_salle		*res;

	if (!(res = (t_salle*)malloc(sizeof(t_salle))))
		return (NULL);
	//res->fourmi = NULL;
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
	if (strstrlen(parts) != 3 || !only_numbers(parts[1]) || !only_numbers(parts[2]))
		return (free_parts_n_return(parts, 0));
	return (free_parts_n_return(parts, 1));
}

char	is_start_or_end_salle(char **line, t_salle **start_salle, t_salle **end_salle)
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
		if (*start_salle != NULL && start_end == 1)
			return (-1);
		if (*end_salle != NULL && start_end == 2)
			return (-1);
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
		t_salle **start_salle, t_salle **end_salle)
{
	char	**parts;
	char	start_end;
	t_salle	*salle;

	start_end = is_start_or_end_salle(line, start_salle, end_salle);
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
		*start_salle = (t_salle*)((*salles_end)->content);
	else if (start_end == 2)
		*end_salle = (t_salle*)((*salles_end)->content);
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
	if (line[1] == '#' && line[2] != '#')
		return (0);
	return (1);
}

t_salle	**parse_salles(t_salle **start_salle, t_salle **end_salle, char **line)
{
	char	input_correct;
	t_list	*salles;
	t_list	*salles_end;
	char	tube_description;

	salles = NULL;
	salles_end = NULL;
	if (get_next_line(0, line) == -1)
		return (NULL);
	input_correct = is_input_correct(*line);
	while (input_correct == 1 && line && ft_strlen(*line) > 0)
	{
		if (!(add_to_salles(&salles_end, line, start_salle, end_salle)))
			return (NULL);
		if (!salles)
			salles = salles_end;
		free(*line);
		if (salle_name_already_used(salles, (t_salle*)salles_end->content))
		{
			free(((t_salle*)salles_end->content)->name);
			free(((t_salle*)salles_end->content));
			free(salles_end);
			salles_end = NULL;
			return (NULL);
		}
		if (get_next_line(0, line) == -1)
			return (NULL);
		input_correct = is_input_correct(*line);
	}
	tube_description = is_tube_description(*line);
	if (input_correct == -1 || (!tube_description && !is_comment(*line)))
	{
		free(*line);
		return (NULL);
	}
	return (list_to_salles(salles));
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

int		get_tubes(t_salle **salles, char *line)
{
	while (is_tube_description(line) || is_comment(line))
	{
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
			salles[i]->accessible_salles[x] = ((t_salle*)*((t_salle**)tmp->content));
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

t_fourm	*get_fourmiliere(t_salle **start_salle, t_salle **end_salle)
{
	t_salle	**salles;
	char	*line;
	int		nb_fourmis;

	if (get_next_line(0, &line) == -1 || !only_numbers(line) || line[0] == '0')
		return (NULL);
	nb_fourmis = ft_atoi(line);
	free(line);
	salles = parse_salles(start_salle, end_salle, &line);
	if (!salles)
		return (NULL);
	if (!(*start_salle) || !(*end_salle))
		return (NULL);
	if (!(get_tubes(salles, line)))
		return (NULL);
	if (!(accessible_list_to_array(salles)))
		return (NULL);
	free_tmp_lists(salles);
	put_salles(salles);
	ft_printf("END SALLE   : %d\nSTART SALLE : %d\n", (*end_salle)->id, (*start_salle)->id);
	return (salles_to_fourmiliere(nb_fourmis, salles, *start_salle, *end_salle));
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

void	add_salles_to_visited_salles(t_list *path, t_list **visited_salles,
												t_list **visited_salles_end)
{
	t_list	*tmp;

	tmp = path;
	while (tmp)
	{
		ft_lstaddend(visited_salles_end, ft_lstnew((int*)tmp->content, sizeof(int)));
		if (!*visited_salles)
			*visited_salles = *visited_salles_end;
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

int		**find_suitable_paths(t_list *finished_paths, int nb_paths)
{
	t_list	*best_paths[nb_paths];
	int		i;
	int		x;
	int		nb;
	int		len;
	t_list	*tmp;
	t_list	*visited_salles;
	t_list	*visited_salles_end;

	visited_salles = NULL;
	visited_salles_end = NULL;
	if (!finished_paths)
		return (NULL);
	len = listlen(finished_paths);
	if (nb_paths == 1)
		return (path_to_int_paths((t_list**)(finished_paths->content), 1));
	i = 0;
	while (i < len - nb_paths)
	{
		best_paths[0] = (t_list*)finished_paths->content;
		visited_salles = NULL;
		visited_salles_end = NULL;
		add_salles_to_visited_salles(best_paths[0], &visited_salles, &visited_salles_end);
		nb = 1;
		x = i + 1;
		tmp = finished_paths->next;
		while (x < len)
		{
			if (no_shared_salle(tmp, visited_salles))
			{
				best_paths[nb] = (t_list*)tmp->content;
				add_salles_to_visited_salles(best_paths[nb], &visited_salles, &visited_salles_end);
				nb++;
			}
			if (nb == nb_paths)
				return (path_to_int_paths(best_paths, nb_paths));
			tmp = tmp->next;
			x++;
		}
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
	tmp = (t_list*)path->content;
	while (tmp)
	{
		ft_lstaddend(&ints_end, ft_lstnew((int*)tmp->content, sizeof(int)));
		if (!ints)
			ints = ints_end;
		tmp = tmp->next;
	}
	if (!(res = ft_lstnew(ints, sizeof(t_list*))))
		return (NULL);
	return (res);
}

int		add_paths_from_salle(t_salle *salle, t_list *path, t_list **paths_end, t_list **finished_paths_end, t_fourm *fourmiliere)
{
	int		i;
	t_list	*tmp;
	int		not_found;
	t_list	*new_list;

	i = 0;
	ft_putendl("add_paths-1");
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
			ft_putendl("add_paths0");
			if (!(new_list = copy_list(path)))
				return (0);
			ft_putendl("add_paths1");
			ft_lstadd(&new_list, ft_lstnew(&salle->accessible_salles[i]->id, sizeof(int)));
			if (*((int*)new_list->content) == fourmiliere->end->id)
				ft_lstaddend(finished_paths_end, new_list);
			else
				ft_lstaddend(paths_end, new_list);
		}
		i++;
	}
	return (1);
}

int		add_step_to_paths(t_list **paths, t_list **paths_end, t_list **finished_paths,
						t_list **finished_paths_end, t_fourm *fourmiliere)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_salle	*last_salle;
	int		len;

	len = listlen(*paths);
	tmp = *paths;
	while (tmp && len > 0)
	{
		ft_putendl("add0");
		ft_printf("last salle : %d\n", *(int*)(((t_list*)tmp->content)->content));
		last_salle = fourmiliere->salles[*(int*)(((t_list*)tmp->content)->content)];
		ft_putendl("add1");
		if (!(add_paths_from_salle(last_salle, (t_list*)tmp->content, paths_end, finished_paths_end, fourmiliere)))
			return (0);
		ft_putendl("add2");
		if (!*finished_paths && *finished_paths_end)
			finished_paths = finished_paths_end;
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
		len--;
	}
	return (1);
}

int		**find_best_paths(t_fourm *fourmiliere, int nb_paths)
{
	int		**res;
	t_list	*paths;
	t_list	*paths_end;
	t_list	*finished_paths;
	t_list	*finished_paths_end;

	if (!(paths = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!(paths->content = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	((t_list*)paths->content)->content = &fourmiliere->start->id;
	/*if (!(paths_end = ft_lstnew(&fourmiliere->start->id, sizeof(int))))
		return (NULL);
	if (!(paths = ft_lstnew(&paths_end, sizeof(t_list*))))
		return (NULL);*/
	//ft_printf("start id : %d\n", *((int*)paths_end->content));
	ft_printf("last salle : %d\n", *((int*)(((t_list*)paths->content)->content)));
	//free((int*)paths_end->content);
	//free(paths_end);
	paths_end = paths;
	finished_paths = NULL;
	finished_paths_end = NULL;
	ft_putendl("LOL");
	while (!(res = find_suitable_paths(finished_paths, nb_paths)) && paths)
	{
		ft_putendl("LOl2");
		if (!(add_step_to_paths(&paths, &paths_end, &finished_paths, &finished_paths_end, fourmiliere)))
			return (NULL);
		ft_putendl("LOL3");
	}
	return (res);
}

int		ft_error(void)
{
	ft_putendl_fd("ERROR", 2);
	return (0);
}

int		main(void)
{
	t_fourm	*fourmiliere;
	t_salle	*start_salle;
	t_salle	*end_salle;
	int		nb_paths_to_find;
	int		**best_paths;

	start_salle = NULL;
	end_salle = NULL;
	if (!(fourmiliere = get_fourmiliere(&start_salle, &end_salle)))
		return (ft_error());
	if (!(nb_paths_to_find = min_end_start(fourmiliere)))
		return (ft_error());
	if (!(best_paths = find_best_paths(fourmiliere, nb_paths_to_find)))
		return (ft_error());
	ft_printf("%p\n", fourmiliere->end);
	return (0);
}
