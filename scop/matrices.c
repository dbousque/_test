

#include "matrices.h"

t_mat	*new_mat(int nb_rows, int nb_columns)
{
	t_mat	*mat;
	int		i;

	if (!(mat = (t_mat*)malloc(sizeof(t_mat))))
		return (NULL);
	if (!(mat->elts = (float*)malloc(sizeof(float) * (nb_rows * nb_columns))))
		return (NULL);
	mat->nb_rows = nb_rows;
	mat->nb_columns = nb_columns;
	i = 0;
	while (i < nb_rows * nb_columns)
	{
		mat->elts[i] = 0.0;
		i++;
	}
	return (mat);
}

t_mat	*new_square_mat(int n)
{
	t_mat	*mat;
	int		i;

	mat = new_mat(n, n);
	if (!mat)
		return (NULL);
	i = 0;
	while (i < n)
	{
		mat->elts[(n * i) + i] = 1.0;
		i++;
	}
	return (mat);
}

t_mat	*new_mat2()
{
	return (new_square_mat(2));
}

t_mat	*new_mat3()
{
	return (new_square_mat(3));
}

t_mat	*new_mat4()
{
	return (new_square_mat(4));
}

t_vec	*new_vec(int n)
{
	return (new_mat(n, 1));
}

t_vec	*new_vec2(float elt1, float elt2)
{
	t_vec	*vec;

	vec = new_vec(2);
	if (!vec)
		return (NULL);
	vec->elts[0] = elt1;
	vec->elts[1] = elt2;
	return (vec);
}

t_vec	*new_vec3(float elt1, float elt2, float elt3)
{
	t_vec	*vec;

	vec = new_vec(3);
	if (!vec)
		return (NULL);
	vec->elts[0] = elt1;
	vec->elts[1] = elt2;
	vec->elts[2] = elt3;
	return (vec);
}

t_vec	*new_vec4(float elt1, float elt2, float elt3, float elt4)
{
	t_vec	*vec;

	vec = new_vec(4);
	if (!vec)
		return (NULL);
	vec->elts[0] = elt1;
	vec->elts[1] = elt2;
	vec->elts[2] = elt3;
	vec->elts[3] = elt4;
	return (vec);
}

void	translate(t_mat *mat, t_vec *vec)
{
	int		i;

	if (mat->nb_rows != vec->nb_rows + 1)
	{
		printf("size error : expected vector of %d\n", mat->nb_rows - 1);
		return ;
	}
	i = 0;
	while (i < vec->nb_rows)
	{
		mat->elts[((i + 1) * mat->nb_columns) - 1] += vec->elts[i];
		i++;
	}
}

void	scaling(t_mat *mat, t_vec *vec)
{
	int		i;

	if (mat->nb_rows != vec->nb_rows + 1)
	{
		printf("size error : expected vector of %d\n", mat->nb_rows - 1);
		return ;
	}
	i = 0;
	while (i < vec->nb_rows)
	{
		mat->elts[(i * mat->nb_columns) + i] *= vec->elts[i];
		i++;
	}
}

void	print_mat(t_mat *mat)
{
	int		i;
	int		j;

	i = 0;
	while (i < mat->nb_rows)
	{
		j = 0;
		while (j < mat->nb_columns)
		{
			printf("%.2f ", mat->elts[(i * mat->nb_columns) + j]);
			j++;
		}
		printf("\n");
		i++;
	}
}