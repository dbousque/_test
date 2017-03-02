

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

t_vec	*vec3_normalize(t_vec *vec)
{
	t_vec	*res;
	float	total;

	total = 0.0;
	total += powf(vec->elts[0], 2.0);
	total += powf(vec->elts[1], 2.0);
	total += powf(vec->elts[2], 2.0);
	total = sqrt(total);
	res = new_vec3(vec->elts[0] / total, vec->elts[1] / total,
														vec->elts[2] / total);
	return (res);
}

float	get_norm(float x, float y, float z)
{
	float	total;

	total = 0.0;
	total += powf(x, 2.0);
	total += powf(y, 2.0);
	total += powf(z, 2.0);
	return (sqrt(total));
}

t_vec	*vec3_sub(t_vec *vec1, t_vec *vec2)
{
	t_vec	*res;

	res = new_vec3(0.0, 0.0, 0.0);
	res->elts[0] = vec1->elts[0] - vec2->elts[0];
	res->elts[1] = vec1->elts[1] - vec2->elts[1];
	res->elts[2] = vec1->elts[2] - vec2->elts[2];
	return (res);
}

t_vec	*vec3_cross(t_vec *vec1, t_vec *vec2)
{
	float	one;
	float	two;
	float	three;

	one = (vec1->elts[1] * vec2->elts[2]) - (vec1->elts[2] * vec2->elts[1]);
	two = (vec1->elts[2] * vec2->elts[0]) - (vec1->elts[0] * vec2->elts[2]);
	three = (vec1->elts[0] * vec2->elts[1]) - (vec1->elts[1] * vec2->elts[0]);
	return (new_vec3(one, two, three));
}

/*void	translate(t_mat *mat, t_vec *vec)
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
}*/

/*void	scale(t_mat *mat, t_vec *vec)
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
}*/

float	mult_row_col(t_mat *mat1, t_mat *mat2, int row1, int column2)
{
	float	val;

	val = mat1->elts[row1 * 4] * mat2->elts[column2];
	val += mat1->elts[row1 * 4 + 1] * mat2->elts[4 + column2];
	val += mat1->elts[row1 * 4 + 2] * mat2->elts[8 + column2];
	val += mat1->elts[row1 * 4 + 3] * mat2->elts[12 + column2];
	return (val);
}

t_mat	*mat_mult(t_mat *mat1, t_mat *mat2)
{
	t_mat	*res;
	int		i;
	int		j;

	res = new_mat4();
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res->elts[i * 4 + j] = mult_row_col(mat1, mat2, i, j);
			j++;
		}
		i++;
	}
	return (res);
}

t_mat	*scale(t_vec *vec)
{
	t_mat	*mat;

	mat = new_mat4();
	mat->elts[0] = vec->elts[0];
	mat->elts[5] = vec->elts[1];
	mat->elts[10] = vec->elts[2];
	return (mat);
}

t_mat	*translate(t_vec *vec)
{
	t_mat	*mat;

	mat = new_mat4();
	mat->elts[3] = vec->elts[0];
	mat->elts[7] = vec->elts[1];
	mat->elts[11] = vec->elts[2];
	return (mat);
}

/*void	*ft_memcpy(char *bytes, size_t len)
{
	char	*res;
	size_t	i;

	if (!(res = (char*)malloc(len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = bytes[i];
		i++;
	}
	return (res);
}*/

float	deg_to_rad(float deg)
{
	return ((deg * 3.14159) / 180);
}

t_mat	*make_rot_x(float rad)
{
	t_mat	*res;
	float	cosv;
	float	sinv;

	res = new_mat4();
	cosv = cosf(rad);
	sinv = sinf(rad);
	res->elts[5] = cosv;
	res->elts[6] = -sinv;
	res->elts[9] = sinv;
	res->elts[10] = cosv;
	return (res);
}

t_mat	*make_rot_y(float rad)
{
	t_mat	*res;
	float	cosv;
	float	sinv;

	res = new_mat4();
	cosv = cosf(rad);
	sinv = sinf(rad);
	res->elts[0] = cosv;
	res->elts[2] = sinv;
	res->elts[8] = -sinv;
	res->elts[10] = cosv;
	return (res);
}

t_mat	*make_rot_z(float rad)
{
	t_mat	*res;
	float	cosv;
	float	sinv;

	res = new_mat4();
	cosv = cosf(rad);
	sinv = sinf(rad);
	res->elts[0] = cosv;
	res->elts[1] = -sinv;
	res->elts[4] = sinv;
	res->elts[5] = cosv;
	return (res);
}

t_mat	*rotate(t_vec *vec)
{
	t_mat	*ret;
	t_mat	*rot_x;
	t_mat	*rot_y;
	t_mat	*rot_z;

	rot_x = make_rot_x(vec->elts[1]);
	rot_y = make_rot_y(vec->elts[2]);
	rot_z = make_rot_z(vec->elts[0]);
	ret = new_mat4();
	ret = mat_mult(ret, rot_x);
	ret = mat_mult(ret, rot_y);
	ret = mat_mult(ret, rot_z);
	return (ret);
}

t_mat	*invert5(float *m, t_mat *res_inv, float *inv)
{
	int		i;
	float	det;

	inv[15] = m[0] * m[5] * m[10] - 
		m[0] * m[6] * m[9] - 
		m[4] * m[1] * m[10] + 
		m[4] * m[2] * m[9] + 
		m[8] * m[1] * m[6] - 
		m[8] * m[2] * m[5];
	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
	if (det == 0.0)
		return (NULL);
	det = 1.0 / det;
	i = 0;
	while (i < 16)
	{
		inv[i] *= det;
		i++;
	}
	return (res_inv);
}

t_mat	*invert4(float *m, t_mat *res_inv, float *inv)
{
	inv[14] = -m[0]  * m[5] * m[14] + 
		m[0]  * m[6] * m[13] + 
		m[4]  * m[1] * m[14] - 
		m[4]  * m[2] * m[13] - 
		m[12] * m[1] * m[6] + 
		m[12] * m[2] * m[5];
	inv[3] = -m[1] * m[6] * m[11] + 
		m[1] * m[7] * m[10] + 
		m[5] * m[2] * m[11] - 
		m[5] * m[3] * m[10] - 
		m[9] * m[2] * m[7] + 
		m[9] * m[3] * m[6];
	inv[7] = m[0] * m[6] * m[11] - 
		m[0] * m[7] * m[10] - 
		m[4] * m[2] * m[11] + 
		m[4] * m[3] * m[10] + 
		m[8] * m[2] * m[7] - 
		m[8] * m[3] * m[6];
	inv[11] = -m[0] * m[5] * m[11] + 
		m[0] * m[7] * m[9] + 
		m[4] * m[1] * m[11] - 
		m[4] * m[3] * m[9] - 
		m[8] * m[1] * m[7] + 
		m[8] * m[3] * m[5];
	return (invert5(m, res_inv, inv));
}

t_mat	*invert3(float *m, t_mat *res_inv, float *inv)
{
	inv[13] = m[0]  * m[9] * m[14] - 
		m[0]  * m[10] * m[13] - 
		m[8]  * m[1] * m[14] + 
		m[8]  * m[2] * m[13] + 
		m[12] * m[1] * m[10] - 
		m[12] * m[2] * m[9];
	inv[2] = m[1]  * m[6] * m[15] - 
		m[1]  * m[7] * m[14] - 
		m[5]  * m[2] * m[15] + 
		m[5]  * m[3] * m[14] + 
		m[13] * m[2] * m[7] - 
		m[13] * m[3] * m[6];
	inv[6] = -m[0]  * m[6] * m[15] + 
		m[0]  * m[7] * m[14] + 
		m[4]  * m[2] * m[15] - 
		m[4]  * m[3] * m[14] - 
		m[12] * m[2] * m[7] + 
		m[12] * m[3] * m[6];
	inv[10] = m[0]  * m[5] * m[15] - 
		m[0]  * m[7] * m[13] - 
		m[4]  * m[1] * m[15] + 
		m[4]  * m[3] * m[13] + 
		m[12] * m[1] * m[7] - 
		m[12] * m[3] * m[5];
	return (invert4(m, res_inv, inv));
}

t_mat	*invert2(float *m, t_mat *res_inv, float *inv)
{
	inv[12] = -m[4]  * m[9] * m[14] + 
		m[4]  * m[10] * m[13] +
		m[8]  * m[5] * m[14] - 
		m[8]  * m[6] * m[13] - 
		m[12] * m[5] * m[10] + 
		m[12] * m[6] * m[9];
	inv[1] = -m[1]  * m[10] * m[15] + 
		m[1]  * m[11] * m[14] + 
		m[9]  * m[2] * m[15] - 
		m[9]  * m[3] * m[14] - 
		m[13] * m[2] * m[11] + 
		m[13] * m[3] * m[10];
	inv[5] = m[0]  * m[10] * m[15] - 
		m[0]  * m[11] * m[14] - 
		m[8]  * m[2] * m[15] + 
		m[8]  * m[3] * m[14] + 
		m[12] * m[2] * m[11] - 
		m[12] * m[3] * m[10];
	inv[9] = -m[0]  * m[9] * m[15] + 
		m[0]  * m[11] * m[13] + 
		m[8]  * m[1] * m[15] - 
		m[8]  * m[3] * m[13] - 
		m[12] * m[1] * m[11] + 
		m[12] * m[3] * m[9];
	return (invert3(m, res_inv, inv));
}

t_mat	*invert(t_mat *inp)
{
    t_mat	*res_inv;
    float	*inv;
    float	*m;

    m = inp->elts;
    res_inv = new_mat4();
    if (!res_inv)
    	return (NULL);
    inv = res_inv->elts;
	inv[0] = m[5]  * m[10] * m[15] - 
		m[5]  * m[11] * m[14] - 
		m[9]  * m[6]  * m[15] + 
		m[9]  * m[7]  * m[14] +
		m[13] * m[6]  * m[11] - 
		m[13] * m[7]  * m[10];
	inv[4] = -m[4]  * m[10] * m[15] + 
		m[4]  * m[11] * m[14] + 
		m[8]  * m[6]  * m[15] - 
		m[8]  * m[7]  * m[14] - 
		m[12] * m[6]  * m[11] + 
		m[12] * m[7]  * m[10];
	inv[8] = m[4]  * m[9] * m[15] - 
		m[4]  * m[11] * m[13] - 
		m[8]  * m[5] * m[15] + 
		m[8]  * m[7] * m[13] + 
		m[12] * m[5] * m[11] - 
		m[12] * m[7] * m[9];
	return (invert2(m, res_inv, inv));
}

t_mat	*transpose(t_mat *mat)
{
	t_mat	*res;
	int		i;
	int		j;

	res = new_mat4();
	i = 0;
	while (i < mat->nb_rows)
	{
		j = 0;
		while (j < mat->nb_columns)
		{
			res->elts[j * mat->nb_rows + i] = mat->elts[i * mat->nb_columns + j];
			j++;
		}
		i++;
	}
	return (res);
}

/*t_mat	*perspective(float x_width, float y_height, float near, float far)
{
	t_mat	*ret;

	ret = new_mat4();
	ret->elts[0] = near / x_width;
	ret->elts[5] = near / y_height;
	ret->elts[10] = (-(far + near) / (far - near));
	ret->elts[11] = (-2.0 * (far * near)) / (far - near);
	ret->elts[14] = -1.0;
	ret->elts[15] = 0.0;
	return (ret);
}*/

t_mat	*perspective(float fov, float ratio, float near, float far)
{
	t_mat	*ret;
	float	fov_norm;

	far /= (far - near);
	fov_norm = 1.0 - tanf(fov / 2.0);
	ret = new_mat4();
	ret->elts[0] = fov_norm;
	ret->elts[5] = fov_norm / ratio;
	ret->elts[10] = far;
	ret->elts[11] = near * far;
	ret->elts[14] = -1.0;
	ret->elts[15] = 0.0;
	return (ret);
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