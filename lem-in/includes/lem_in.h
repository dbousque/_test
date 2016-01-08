

#ifndef LEM_IN_H
# define LEM_IN_H

#include "libdodo.h"

typedef struct		s_salle
{
	char			*name;
	struct s_salle	**accessible_salles;
	t_list			*tmp_accessible_salles;
	t_list			*tmp_accessible_salles_end;
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

typedef struct	s_fourmi
{
	int			*path;
	int			current_salle;
	int			id;
}				t_fourmi;

char			is_tube_description(char *line);
char			is_comment(char *line);
char			only_numbers(char *str);
char			is_input_correct(char *line);
t_salle			**parse_salles(t_salle **start_salle, t_salle **end_salle,
											char **line, t_list **lines_end);
t_fourmi		*new_fourmi(int *path, int path_len);
t_salle			*new_salle(char *name, int x_coord, int y_coord);
t_salle			**list_to_salles(t_list *salles);
char			is_start_or_end_salle(char **line, t_salle **start_salle,
									t_salle **end_salle, t_list **lines_end);
int				strstrlen(char **strstr);
char			add_to_salles(t_list **salles_end, char **line,
									t_salle **str_end[2], t_list **lines_end);
void			put_salle(t_salle *salle);
void			put_salles(t_salle **salles);
int				get_tubes(t_salle **salles, char *line, t_list **lines_end);
t_fourm			*get_fourmiliere(t_salle **start_salle, t_salle **end_salle,
																t_list **lines);
int				listlen(t_list *list);

#endif
