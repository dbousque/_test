

#include "particle_system.h"

char	call_kernel_with_args(t_cl_program *program, void **args, size_t *sizes, size_t nb_args)
{
	cl_int	ret;
	size_t	i;

	i = 0;
	while (i < nb_args)
	{
		ret = clSetKernelArg(program->kernel, i, sizes[i], args[i]);
		if (ret != CL_SUCCESS)
			return (cl_operation_failed(program, "clSetKernelArg", ret));
		i++;
	}
	ret = clEnqueueTask(program->command_queue, program->kernel, 0, NULL, NULL);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(program, "clEnqueueTask", ret));
	return (1);
}

char	call_kernel(t_cl_program *program, t_cl_buffer *buffer, unsigned int nb_particles)
{
	void	*args[4];
	size_t	args_size[4];
	float center_gravity_x;
	float center_gravity_y;

	center_gravity_x = 12.4;
	center_gravity_y = 4.2;
	args[0] = &center_gravity_x;
	args[1] = &center_gravity_y;
	args[2] = &nb_particles;
	args[3] = &(buffer->buffer);
	args_size[0] = sizeof(float);
	args_size[1] = sizeof(float);
	args_size[2] = sizeof(unsigned int);
	args_size[3] = sizeof(cl_mem);
	if (!(call_kernel_with_args(program, args, args_size, 4)))
		return (0);
	return (1);
}

char	print_buffer_content(t_cl_program *program, t_cl_buffer *buffer,
													unsigned int nb_particles)
{
	t_particle		*particles;
	unsigned int	i;
	cl_int			ret;

	if (!(particles = (t_particle*)malloc(sizeof(t_particle) * nb_particles)))
	{
		printf("malloc error\n");
		return (0);
	}
	/* Copy results from the memory buffer */
	ret = clEnqueueReadBuffer(program->command_queue, buffer->buffer, CL_TRUE, 0,
		sizeof(t_particle) * nb_particles, particles, 0, NULL, NULL);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(program, "clEnqueueReadBuffer", ret));
	i = 0;
	while (i < nb_particles)
	{
		printf("[x : %.3f, y : %.3f]\n", particles[i].x, particles[i].y);
		i++;
	}
	return (1);
}

char	init_opengl(int width, int height, char *title_name)
{
	t_window	window;

	if (!(setup_window(width, height, title_name, &window)))
		return (0);
	return (1);
}

int		main(void)
{
	unsigned int		nb_particles;
	size_t				file_size;
	t_cl_program		cl_program;
	t_cl_buffer			cl_buffer;
	t_gl_program		gl_program;
	t_gl_buffer			gl_buffer;
	char				*source_str;

	nb_particles = 120;

	use clGetGLContextInfoKHR to create (?) CL context from GL context

	init_opengl(800, 800, "salut title");
	if (!(make_gl_program("shaders/vertex.vs", "shaders/fragment.fs", &gl_program)))
		return (0);
	if (!(make_gl_buffer(nb_particles, &gl_buffer)))
		return (0);

	if (!(source_str = get_file_source("hello.cl", &file_size)))
		return (0);
	if (!(make_cl_program(source_str, file_size, "calculate_particles_position", &cl_program)))
		return (0);
	free(source_str);
	if (!(make_cl_buffer(&cl_program, &gl_buffer, &cl_buffer)))
		return (0);

	clFinish(cl_program.command_queue);
	glFinish();
	// LOOK FOR EVENTS TO FINISH ???
	clEnqueueAcquireGLObjects(cl_program.command_queue, 1, &(cl_buffer.buffer), 0, NULL, NULL);

	clFinish(cl_program.command_queue);

	if (!call_kernel(&cl_program, &cl_buffer, nb_particles))
		return (0);
	if (!print_buffer_content(&cl_program, &cl_buffer, nb_particles))
		return (0);

	finalize_buffer(&cl_buffer);
	finalize_cl_program(&cl_program);

	//sleep(3);
 
	return (0);
}