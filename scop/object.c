

#include "myopengl.h"

GLuint	make_texture(char *img_path)
{
	int				width;
	int				height;
	unsigned char	*img;
	GLuint			texture;

	img = SOIL_load_image(img_path, &width, &height, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(img);
	glBindTexture(GL_TEXTURE_2D, 0);
    return (texture);
}

void	load_texture_to_obj(t_globj *obj, char *img_path)
{
	obj->texture = make_texture(img_path);
	obj->has_texture = 1;
}

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
	obj->has_texture = 0;
	obj->has_indices = 0;
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
	glBindVertexArray(0);
	return (obj);
}

void	attach_indices_to_obj(t_globj *obj, GLuint indices[], int nb_indices)
{
	glBindVertexArray(obj->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &(obj->EBO));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * nb_indices, indices,
															GL_STATIC_DRAW);
	glBindVertexArray(0);
	obj->has_indices = 1;
	obj->nb_indices = nb_indices;
}

void	draw_object(t_shader_program *shader_program, t_globj *obj)
{
	if (obj->has_texture)
		glBindTexture(GL_TEXTURE_2D, obj->texture);
	glUseProgram(shader_program->program);
	glBindVertexArray(obj->VAO);
	if (obj->has_indices)
		glDrawElements(GL_TRIANGLES, obj->nb_indices, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, obj->nb_vertices);
	glBindVertexArray(0);
}