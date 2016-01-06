

#include "lem_in.h"

typedef struct		s_salle
{
	char			*name;
	t_list			*accessible_salles;
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

t_salle	**parse_salles(t_salle **start_salle, t_salle **end_salle, char *line)
{
	char	input_correct;
	t_list	*salles;
	t_list	*salles_end;

	salles = NULL;
	salles_end = NULL;
	if (get_next_line(0, &line) == -1)
		return (NULL);
	input_correct = is_input_correct(line);
	while (input_correct == 1 && line && ft_strlen(line) > 0)
	{
		if (!(add_to_salles(&salles_end, &line, start_salle, end_salle)))
			return (NULL);
		if (!salles)
			salles = salles_end;
		free(line);
		if (get_next_line(0, &line) == -1)
			return (NULL);
		input_correct = is_input_correct(line);
	}
	free(line);
	if (input_correct == -1)
		return (NULL);
	return (list_to_salles(salles));
}

void	put_salle(t_salle *salle)
{
	ft_printf("SALLE N %d :\n  - NAME : %s\n  - X : %d\n  - Y : %d\n", salle->id, salle->name, salle->x_coord, salle->y_coord);
}

t_fourm	*get_fourmiliere(t_salle **start_salle, t_salle **end_salle)
{
	t_fourm	*res;
	t_salle	**salles;
	char	*line;
	int		i;

	if (!(line = (char*)malloc(sizeof(char))))
		return (NULL);
	salles = parse_salles(start_salle, end_salle, line);
	i = 0;
	while (salles[i])
	{
		put_salle(salles[i]);
		i++;
	}
	res = NULL;
	return (res);
}

int		main(void)
{
	t_fourm	*fourmiliere;
	t_salle	*start_salle;
	t_salle	*end_salle;

	start_salle = NULL;
	end_salle = NULL;
	fourmiliere = get_fourmiliere(&start_salle, &end_salle);
}
