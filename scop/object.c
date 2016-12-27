

#include "myopengl.h"

int		get_texture_nb(int nb)
{
	if (nb == 0)
		return (GL_TEXTURE0);
	if (nb == 1)
		return (GL_TEXTURE1);
	if (nb == 2)
		return (GL_TEXTURE2);
	if (nb == 3)
		return (GL_TEXTURE3);
	if (nb == 4)
		return (GL_TEXTURE4);
	if (nb == 5)
		return (GL_TEXTURE5);
	if (nb == 6)
		return (GL_TEXTURE6);
	if (nb == 7)
		return (GL_TEXTURE7);
	if (nb == 8)
		return (GL_TEXTURE8);
	if (nb == 9)
		return (GL_TEXTURE9);
	if (nb == 10)
		return (GL_TEXTURE10);
	if (nb == 11)
		return (GL_TEXTURE11);
	if (nb == 12)
		return (GL_TEXTURE12);
	if (nb == 13)
		return (GL_TEXTURE13);
	if (nb == 14)
		return (GL_TEXTURE14);
	if (nb == 15)
		return (GL_TEXTURE15);
	return (0);
}

GLuint	make_texture(char *img_path)
{
	int				width;
	int				height;
	unsigned char	*img;
	GLuint			texture;

	img = SOIL_load_image(img_path, &width, &height, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
													GL_UNSIGNED_BYTE, img);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(img);
	glBindTexture(GL_TEXTURE_2D, 0);
    return (texture);
}

void	load_texture_to_obj(t_globj *obj, char *img_path)
{
	GLuint	texture;
	GLuint	*new_textures;
	int		i;

	texture = make_texture(img_path);
	if (!(new_textures = (GLuint*)malloc(sizeof(GLuint)
												* (obj->nb_textures + 1))))
	{
		ft_putstr("malloc error, could not load texture\n");
		return ;
	}
	i = 0;
	while (i < obj->nb_textures)
	{
		new_textures[i] = obj->textures[i];
		i++;
	}
	new_textures[i] = texture;
	if (i > 0)
		free(obj->textures);
	obj->textures = new_textures;
	obj->has_textures = 1;
	obj->nb_textures++;
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

void	*cpy_array(void *array, size_t size)
{
	char	*to_cpy;
	char	*res;
	size_t	i;

	if (!(res = (char*)malloc(size)))
		return (NULL);
	to_cpy = (char*)array;
	i = 0;
	while (i < size)
	{
		res[i] = to_cpy[i];
		i++;
	}
	return (res);
}

t_globj		*new_object(GLfloat *vertices, int nb_vertices,
										int attribs_struct[], int nb_attribs)
{
	t_globj	*obj;
	size_t	tot_data_len;

	if (!(obj = (t_globj*)malloc(sizeof(t_globj))))
	{
		ft_putstr("malloc error\n");
		return (NULL);
	}
	obj->nb_vertices = nb_vertices;
	obj->has_textures = 0;
	obj->has_indices = 0;
	obj->nb_textures = 0;
	obj->textures = NULL;
	obj->shader = NULL;
	obj->x = 0.0;
	obj->y = 0.0;
	obj->z = 0.0;
	obj->normal_mode = 0;
	tot_data_len = sizeof(GLfloat)
					* (nb_vertices * int_arr_sum(attribs_struct, nb_attribs));
	glGenVertexArrays(1, &(obj->VAO1));
	glBindVertexArray(obj->VAO1);
	glGenBuffers(1, &(obj->VBO1));
	glBindBuffer(GL_ARRAY_BUFFER, obj->VBO1);
	glBufferData(GL_ARRAY_BUFFER, tot_data_len,
									(GLfloat const*)vertices, GL_STATIC_DRAW);
	init_vertex_attributes(attribs_struct, nb_attribs, nb_vertices,
																tot_data_len);
	glBindVertexArray(0);

	GLfloat		*vertices_cpy;

	vertices_cpy = cpy_array(vertices, sizeof(GLfloat) * 8 * nb_vertices);
	calculate_raw_normals(vertices_cpy, nb_vertices);

	glGenVertexArrays(1, &(obj->VAO2));
	glBindVertexArray(obj->VAO2);
	glGenBuffers(1, &(obj->VBO2));
	glBindBuffer(GL_ARRAY_BUFFER, obj->VBO2);
	glBufferData(GL_ARRAY_BUFFER, tot_data_len,
									(GLfloat const*)vertices_cpy, GL_STATIC_DRAW);
	init_vertex_attributes(attribs_struct, nb_attribs, nb_vertices,
																tot_data_len);
	glBindVertexArray(0);

	return (obj);
}

void	attach_indices_to_obj(t_globj *obj, GLuint indices[], int nb_indices)
{
	glBindVertexArray(obj->VAO1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &(obj->EBO1));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->EBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * nb_indices, indices,
															GL_STATIC_DRAW);
	glBindVertexArray(0);

	glBindVertexArray(obj->VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &(obj->EBO2));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * nb_indices, indices,
															GL_STATIC_DRAW);
	glBindVertexArray(0);

	obj->has_indices = 1;
	obj->nb_indices = nb_indices;
}

void	attach_shader_program_to_obj(t_globj *obj, t_shader_program *shader)
{
	obj->shader = shader;
}

void	activate_textures(t_shader_program *shader_program, t_globj *obj)
{
	int		i;
	char	*tmp_text_name;
	char	*i_str;

	i = 0;
	while (i < obj->nb_textures)
	{
		i_str = ft_itoa(i);
		tmp_text_name = ft_strconcat("ourTexture", i_str);
		glActiveTexture(get_texture_nb(i));
		glBindTexture(GL_TEXTURE_2D, obj->textures[i]);
		glUniform1i(glGetUniformLocation(shader_program->program,
														tmp_text_name), i);
		free(i_str);
		free(tmp_text_name);
		i++;
	}
}

void	draw_object(t_shader_program *shader_program, t_globj *obj)
{
	if (obj->has_textures)
		activate_textures(shader_program, obj);
	glUseProgram(shader_program->program);
	if (obj->normal_mode == 0)
		glBindVertexArray(obj->VAO1);
	else
		glBindVertexArray(obj->VAO2);
	if (obj->has_indices)
		glDrawElements(GL_TRIANGLES, obj->nb_indices, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, obj->nb_vertices);
	glBindVertexArray(0);
}