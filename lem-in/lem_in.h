

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

#endif
