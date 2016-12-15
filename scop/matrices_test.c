

#include "matrices.h"

int		main(void)
{
	t_mat	*mat;
	t_vec	*vec;

	mat = new_mat4();
	vec = new_vec4(1.2, 0.3, 0.0, 0.4);
	print_mat(mat);
	translate(mat, new_vec3(2.0, 1.0, 0.5));
	printf("\n");
	print_mat(mat);
	scaling(mat, new_vec3(2.0, 2.0, 2.0));
	printf("\n");
	print_mat(mat);
	printf("\n");
	print_mat(vec);
	return (0);
}