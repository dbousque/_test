

#include "lem-in.h"

typedef struct		s_salle
{
	char			*name;
	struct s_salle	links_to;
	t_fourmi		*fourmi;
}					t_salle;

typedef struct	s_fourm
{
	t_salle		**salles;
	int			nb_fourmis;
	t_salle		*start;
	t_salle		*end;
}				t_fourm;

t_fourm	*get_fourmiliere(void)
{
	t_fourm	*res;

	
}
