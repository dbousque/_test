

#ifndef MYOPENGL_H
# define MYOPENGL_H

# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <GLUT/glut.h>
#  include <OpenGL/glu.h>
# endif
# include "SOIL.h"
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "matrices.h"

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
	GLuint		EBO;
	int			nb_vertices;
	int			nb_indices;
	char		has_indices;
	char		has_textures;
	GLuint		*textures;
	int			nb_textures;
}				t_globj;

typedef struct	s_window
{
	GLFWwindow	*win;
}				t_window;

typedef struct	s_camera
{
	float		x;
	float		y;
	float		z;
	float		front_x;
	float		front_y;
	float		front_z;
	float		up_x;
	float		up_y;
	float		up_z;
	float		speed;
	float		fov;
	float		pitch;
	float		yaw;
	float		roll;
}				t_camera;

t_camera			g_cam;

size_t				ft_strlen(char *str);
void				ft_putstr(char *str);
char				*ft_itoa(int n);
char				*ft_strconcat(char *st1, char *st2);
char				*read_file(char *filename, size_t max_size);
void    			key_callback(GLFWwindow *window, int key, int scancode,
														int action, int mode);
t_shader_program	*new_shader_program(char *vertex_shader_path,
												char *fragment_shader_path);
t_window			*setup_window(int width, int height, char *title_name);
void				draw_object(t_shader_program *shader_program,
																t_globj *obj);
t_globj				*new_object(GLfloat *vertices, int attribs_struct[],
											int nb_attribs, int nb_vertices);
void				load_texture_to_obj(t_globj *obj, char *img_path);
void				attach_indices_to_obj(t_globj *obj, GLuint indices[],
															int nb_indices);

#endif
