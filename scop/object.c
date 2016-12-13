

#include "myopengl.h"

int		int_arr_sum(int arr[], int nb)
{
	int		i;
	int		sum;

	sum = 0;
	i = 0;
	while (i < nb)
	{
		sum += arr[i];
		i++;
	}
	return (sum);
}

void	init_vertex_attributes(int attribs_struct[], int nb_attribs,
										int nb_vertices, size_t tot_data_len)
{
	int		i;
	int		seen_vars;

	seen_vars = 0;
	i = 0;
	while (i < nb_attribs)
	{
		glVertexAttribPointer(i, attribs_struct[i], GL_FLOAT, GL_FALSE,
		tot_data_len / nb_vertices, (GLvoid*)(seen_vars * sizeof(GLfloat)));
		glEnableVertexAttribArray(i);
		seen_vars += attribs_struct[i];
		i++;
	}
	glBindVertexArray(0);
}

t_globj		*new_object(GLfloat *vertices, int attribs_struct[],
											int nb_attribs, int nb_vertices)
{
	t_globj	*obj;
	size_t	tot_data_len;

	if (!(obj = (t_globj*)malloc(sizeof(t_globj))))
	{
		ft_putstr("malloc error\n");
		return (NULL);
	}
	obj->nb_vertices = nb_vertices;
	glGenVertexArrays(1, &(obj->VAO));
	glBindVertexArray(obj->VAO);
	glGenBuffers(1, &(obj->VBO));
	glBindBuffer(GL_ARRAY_BUFFER, obj->VBO);
	tot_data_len = sizeof(GLfloat)
					* (nb_vertices * int_arr_sum(attribs_struct, nb_attribs));
	glBufferData(GL_ARRAY_BUFFER, tot_data_len,
									(GLfloat const*)vertices, GL_STATIC_DRAW);
	init_vertex_attributes(attribs_struct, nb_attribs, nb_vertices,
																tot_data_len);
	return (obj);
}

void	draw_object(t_shader_program *shader_program, t_globj *obj)
{
	glUseProgram(shader_program->program);
	glBindVertexArray(obj->VAO);
	glDrawArrays(GL_TRIANGLES, 0, obj->nb_vertices);
	glBindVertexArray(0);
}