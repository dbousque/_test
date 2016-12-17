

#ifndef MATRICES_H
# define MATRICES_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>

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
t_mat			*mat_mult(t_mat *mat1, t_mat *mat2);
t_mat			*translate(t_vec *vec);
t_mat			*scale(t_vec *vec);
t_mat			*rotate(t_vec *rotate);
float			deg_to_rad(float deg);
void			print_mat(t_mat *mat);

#endif