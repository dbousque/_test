

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

typedef struct	s_list
{
	void		*elts;
	size_t		size;
	size_t		len;
	size_t		elt_size;
}				t_list;

typedef struct	s_objfile
{
	char		*objname;
	t_list		*vertices;
	t_list		*texture;
	t_list		*normals;
	t_list		*faces;
}				t_objfile;

typedef struct	s_config
{
	char		lines;
	float		obj_scale;
	int			win_width;
	int			win_height;
}				t_config;

t_camera			g_cam;
char				g_keys[1024];
t_config			g_conf;

t_list				*new_list(size_t elt_size);
void				add_to_list(t_list *lst, void *elt);
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
t_globj				*new_object(GLfloat *vertices, int nb_vertices,
										int attribs_struct[], int nb_attribs);
void				load_texture_to_obj(t_globj *obj, char *img_path);
void				attach_indices_to_obj(t_globj *obj, GLuint indices[],
															int nb_indices);
t_objfile			*parse_objfile(char *path);
char				add_vertex(t_objfile *objfile, char *line, size_t line_nb);
char				add_face(t_objfile *objfile, char *line, size_t line_nb);
void				update_camera(void);
void				init_camera(void);
void				do_movement(GLfloat delta_time);
void    			key_callback(GLFWwindow *window, int key, int scancode,
														int action, int mode);
void				setup_keys(void);
char				objfile_to_vertices(t_objfile *objfile, GLfloat **vertices,
															int *nb_vertices);

#endif
