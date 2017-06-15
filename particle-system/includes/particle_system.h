

#ifndef PARTICLE_SYSTEM_H
# define PARTICLE_SYSTEM_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <GL/glew.h>
# include <GLFW/glfw3.h>
 
# ifdef __APPLE__
#	include <OpenCL/opencl.h>
#	include <OpenCL/cl_gl.h>
#	include <OpenGL/gl.h>
#	include <GLUT/glut.h>
#	include <OpenGL/glu.h>
# else
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
	cl_kernel			kernel;
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
	float				x;
	float				y;
}						t_particle;

char					*get_file_source(char *filename, size_t *size);
char					setup_window(int width, int height, char *title_name,
															t_window *window);
char					make_cl_buffer(t_cl_program *program,
									t_gl_buffer *gl_buffer, t_cl_buffer *res);
void					finalize_buffer(t_cl_buffer *buffer);
char					cl_operation_failed(t_cl_program *program, char *msg,
															cl_int error_code);
char					make_gl_buffer(int nb_particles, t_gl_buffer *buffer);
void					draw_gl_buffer(t_gl_program *gl_program,
							t_gl_buffer *buffer, unsigned int nb_particles);
char					make_gl_program(char *vertex_shader_path,
							char *fragment_shader_path, t_gl_program *program);
char					make_cl_program(char *source_str, size_t file_size,
										char *kernel_name, t_cl_program *res);
void					finalize_cl_program(t_cl_program *program);

#endif