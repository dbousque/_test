

#ifndef PARTICLE_SYSTEM_H
# define PARTICLE_SYSTEM_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <GL/glew.h>
# include <GLFW/glfw3.h>
 
# ifdef __APPLE__
#	include <OpenCL/opencl.h>
#	include <OpenGL/gl.h>
#	include <GLUT/glut.h>
#	include <OpenGL/glu.h>
# else
#	include <CL/cl.h>
# endif

# define FILE_MAX_SIZE (5 * 1024 * 1024)

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

typedef struct			s_window
{
	GLFWwindow			*win;
}						t_window;

t_window				*setup_window(int width, int height, char *title_name);

#endif