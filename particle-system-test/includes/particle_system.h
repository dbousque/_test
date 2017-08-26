

#ifndef PARTICLE_SYSTEM_H
# define PARTICLE_SYSTEM_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <GL/glew.h>
# include <GLFW/glfw3.h>
 
# ifdef __APPLE__
#	include <GL/glx.h>
#	include <OpenCL/opencl.h>
#	include <OpenCL/cl_gl.h>
#	include <OpenCL/cl_gl_ext.h>
#	include <OpenGL/gl.h>
#	include <OpenGL/OpenGL.h>
#	include <GLUT/glut.h>
#	include <OpenGL/glu.h>
# else
#	include <GL/glx.h>
#	include <CL/cl.h>
#	include <CL/cl_gl.h>
# endif

# define FILE_MAX_SIZE (5 * 1024 * 1024)

typedef struct			s_window
{
	GLFWwindow			*win;
}						t_window;

typedef struct			s_gl_program
{
	GLuint				vertex_shader;
	GLuint				fragment_shader;
	GLuint				program;
}						t_gl_program;

typedef struct			s_cl_program
{
	cl_command_queue	command_queue;
	cl_context			context;
	cl_program			program;
	cl_device_id		device_id;
	cl_platform_id		platform_id;
}						t_cl_program;

typedef struct			s_cl_buffer
{
	cl_mem				buffer;
}						t_cl_buffer;

typedef struct			s_gl_buffer
{
	GLuint				vao;
	GLuint				vbo;
}						t_gl_buffer;

typedef struct			s_particle
{
	float				mass;
	float				x;
	float				y;
	float				velocity_x;
	float				velocity_y;
}						t_particle;

typedef struct			s_kernel_data
{
	float				time_delta;
	float				gravity_strength;
	float				center_gravity_x;
	float				center_gravity_y;
	char				center_gravity_activated;
	unsigned int		nb_particles;
	unsigned int		batch_size;
}						t_kernel_data;

char					g_keys[1024];
unsigned int			g_screen_width;
unsigned int			g_screen_height;
float					g_zoom_factor;
float					g_gravity_strength;
float					g_center_gravity_x;
float					g_center_gravity_y;
float					g_view_decal_x;
float					g_view_decal_y;
char					g_center_gravity_lock;
char					g_center_gravity_activated;
char					g_particles_locked;
float					g_mouse_position_x;
float					g_mouse_position_y;

char					*get_file_source(char *filename, size_t *size);
char					setup_window(int width, int height, char *title_name,
															t_window *window);
char					make_cl_buffer(t_cl_program *program,
									t_gl_buffer *gl_buffer, t_cl_buffer *res);
char					make_raw_cl_buffer(t_cl_program *program,
															t_cl_buffer *res);
void					finalize_buffer(t_cl_buffer *buffer);
char					cl_operation_failed(t_cl_program *program, char *msg,
															cl_int error_code);
char					make_gl_buffer(int nb_particles, t_gl_buffer *buffer);
void					draw_gl_buffer(t_gl_program *gl_program,
							t_gl_buffer *buffer, unsigned int nb_particles);
char					make_gl_program(char *vertex_shader_path,
							char *fragment_shader_path, t_gl_program *program);
char					make_cl_program(char *source_str, size_t file_size,
															t_cl_program *res);
void					finalize_cl_program(t_cl_program *program);
char					make_kernel(t_cl_program *program, char *name,
															cl_kernel *kernel);
void					update_values_with_keys(void);

#endif