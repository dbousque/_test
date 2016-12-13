

#ifndef MYOPENGL_H
# define MYOPENGL_H

# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define MAX_SHADER_SIZE 32768
# define READ_BUFFER_LEN 4096

typedef struct	s_shader_program
{
	GLuint		vertex_shader;
	GLuint		fragment_shader;
	GLuint		program;
}				t_shader_program;

typedef struct	s_globj
{
	GLuint		VAO;
	GLuint		VBO;
	int			nb_vertices;
}				t_globj;

typedef struct	s_window
{
	GLFWwindow	*win;
}				t_window;

size_t				ft_strlen(char *str);
void				ft_putstr(char *str);
char				*read_file(char *filename, size_t max_size);
t_shader_program	*new_shader_program(char *vertex_shader_path,
												char *fragment_shader_path);
t_window			*setup_window(int width, int height, char *title_name);
void				draw_object(t_shader_program *shader_program,
																t_globj *obj);
t_globj				*new_object(GLfloat *vertices, int attribs_struct[],
											int nb_attribs, int nb_vertices);

#endif