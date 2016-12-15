

#ifndef MATRICES_H
# define MATRICES_H

#include <stdlib.h>
#include <stdio.h>

typedef struct	s_mat
{
	float		*elts;
	int			nb_rows;
	int			nb_columns;
}				t_mat;

typedef t_mat t_vec;

t_mat			*new_mat(int nb_rows, int nb_columns);
t_mat			*new_mat2();
t_mat			*new_mat3();
t_mat			*new_mat4();
t_vec			*new_vec(int n);
t_vec			*new_vec2(float elt1, float elt2);
t_vec			*new_vec3(float elt1, float elt2, float elt3);
t_vec			*new_vec4(float elt1, float elt2, float elt3, float elt4);
void			translate(t_mat *mat, t_vec *vec);
void			scaling(t_mat *mat, t_vec *vec);
void			print_mat(t_mat *mat);

#endif