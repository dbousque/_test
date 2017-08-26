

#include "particle_system.h"

char	call_kernel_with_args(t_cl_program *program, cl_kernel *kernel,
			void **args, size_t *sizes, size_t nb_args, char data_parallel,
												unsigned int nb_particles)
{
	cl_int	ret;
	size_t	i;
	size_t	work_size;
	size_t	local_size;

	work_size = nb_particles / 64;
	local_size = 1;
	i = 0;
	while (i < nb_args)
	{
		ret = clSetKernelArg(*kernel, i, sizes[i], args[i]);
		if (ret != CL_SUCCESS)
			return (cl_operation_failed(program, "clSetKernelArg", ret));
		i++;
	}
	if (data_parallel)
	{
		ret = clEnqueueNDRangeKernel(program->command_queue, *kernel, 1, NULL,
											&work_size, &local_size, 0, NULL, NULL);
	}
	else
		ret = clEnqueueTask(program->command_queue, *kernel, 0, NULL, NULL);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(program, "clEnqueueTask", ret));
	return (1);
}

char	call_set_kernel(t_cl_program *program, cl_kernel *kernel, t_cl_buffer *buffer,
															unsigned int nb_particles)
{
	void	*args[2];
	size_t	args_size[2];

	args[0] = &nb_particles;
	args[1] = &(buffer->buffer);
	args_size[0] = sizeof(unsigned int);
	args_size[1] = sizeof(cl_mem);
	if (!(call_kernel_with_args(program, kernel, args, args_size, 2, 0, nb_particles)))
		return (0);
	return (1);
}

char	call_update_kernel(t_cl_program *program, cl_kernel *kernel, t_cl_buffer *buffer,
				unsigned int nb_particles, t_cl_buffer *data_buffer, float time_delta)
{
	void			*args[2];
	size_t			args_size[2];

	t_kernel_data	data;

	data.time_delta = time_delta;
	data.gravity_strength = g_gravity_strength;
	data.center_gravity_x = g_center_gravity_x;
	data.center_gravity_y = g_center_gravity_y;
	data.center_gravity_activated = g_center_gravity_activated;
	data.nb_particles = nb_particles;
	data.batch_size = 64;

	(void)data_buffer;

	args[0] = &(data);
	args[1] = &(buffer->buffer);
	args_size[0] = sizeof(t_kernel_data);
	args_size[1] = sizeof(cl_mem);
	if (!(call_kernel_with_args(program, kernel, args, args_size, 2, 1, nb_particles)))
		return (0);
	return (1);
}

char	update_kernel_data_func(t_cl_program *program, cl_kernel *update_kernel_data,
			t_cl_buffer *data_buffer, float time_delta, float gravity_strength,
			float center_gravity_x, float center_gravity_y, unsigned int nb_particles)
{
	void			*args[8];
	unsigned int	batch_size;
	size_t			args_size[8];

	batch_size = 64;
	args[0] = &time_delta;
	args[1] = &gravity_strength;
	args[2] = &center_gravity_x;
	args[3] = &center_gravity_y;
	args[4] = &g_center_gravity_activated;
	args[5] = &nb_particles;
	args[6] = &batch_size;
	args[7] = &(data_buffer->buffer);
	args_size[0] = sizeof(float);
	args_size[1] = sizeof(float);
	args_size[2] = sizeof(float);
	args_size[3] = sizeof(float);
	args_size[4] = sizeof(char);
	args_size[5] = sizeof(unsigned int);
	args_size[6] = sizeof(unsigned int);
	args_size[7] = sizeof(cl_mem);
	if (!(call_kernel_with_args(program, update_kernel_data, args, args_size, 8, 1, nb_particles)))
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
		printf("[x : %.3f, y : %.3f, vel_x : %.3f, vel_y : %.3f]\n", particles[i].x, particles[i].y, particles[i].velocity_x, particles[i].velocity_y);
		i++;
	}
	return (1);
}

char	init_opengl(int width, int height, char *title_name, t_window *window)
{
	if (!(setup_window(width, height, title_name, window)))
		return (0);
	return (1);
}



	# include <sys/time.h>

char	update_particles_positions(t_cl_program *cl_program, cl_kernel *update_kernel,
			t_cl_buffer *cl_buffer, unsigned int nb_particles, t_cl_buffer *data_buffer, float time_delta)
{
	struct timeval stop, start;
	gettimeofday(&start, NULL);
	glFinish();
	gettimeofday(&stop, NULL);
	printf("gl : took %lums\n", (stop.tv_usec - start.tv_usec) / 1000);
	gettimeofday(&start, NULL);
	clEnqueueAcquireGLObjects(cl_program->command_queue, 1,
										&(cl_buffer->buffer), 0, NULL, NULL);

	if (!call_update_kernel(cl_program, update_kernel, cl_buffer, nb_particles, data_buffer, time_delta))
	{
		return (0);
	}
	//if (!print_buffer_content(cl_program, cl_buffer, nb_particles))
	//	return (0);
	clEnqueueReleaseGLObjects(cl_program->command_queue, 1,
										&(cl_buffer->buffer), 0, NULL, NULL);


	clFinish(cl_program->command_queue);
	gettimeofday(&stop, NULL);
	printf("cl : took %lums\n", (stop.tv_usec - start.tv_usec) / 1000);
	return (1);
}

char	set_particles_values(t_cl_program *cl_program, cl_kernel *set_kernel,
								t_cl_buffer *cl_buffer, unsigned int nb_particles)
{
	glFinish();
	clEnqueueAcquireGLObjects(cl_program->command_queue, 1,
										&(cl_buffer->buffer), 0, NULL, NULL);
	if (!call_set_kernel(cl_program, set_kernel, cl_buffer, nb_particles))
		return (0);
	//if (!print_buffer_content(cl_program, cl_buffer, nb_particles))
	//	return (0);
	clEnqueueReleaseGLObjects(cl_program->command_queue, 1,
										&(cl_buffer->buffer), 0, NULL, NULL);
	clFinish(cl_program->command_queue);
	return (1);
}

void	set_window_title_with_time(t_window *window, float time_delta)
{
	size_t	nb_frames_per_sec;
	size_t	micros;
	char	nb_str[20];

	micros = ((int)(time_delta * 1000000.0)) % 1000000;
	nb_frames_per_sec = 1000000 / micros;
	sprintf(nb_str, "%lu fps", nb_frames_per_sec);
	glfwSetWindowTitle(window->win, nb_str);
}

void	main_loop(t_window *window, t_cl_program *cl_program, t_cl_buffer *cl_buffer,
		t_gl_program *gl_program, t_gl_buffer *gl_buffer, cl_kernel *update_kernel,
			cl_kernel *set_kernel, cl_kernel *update_kernel_data,
								t_cl_buffer *data_buffer, unsigned int nb_particles)
{
	char	exit;
	float	tmp_time;
	float	time_delta;
	GLint	loc;
	int		i;

	i = 0;
	exit = 0;
	if (!(set_particles_values(cl_program, set_kernel, cl_buffer, nb_particles)))
	{
		printf("could not set particles values. Exiting...\n");
		exit = 1;
	}
	tmp_time = glfwGetTime();
	while (!exit)
	{
		glfwPollEvents();
		update_values_with_keys();
		loc = glGetUniformLocation(gl_program->program, "zoom_factor");
		glUniform1f(loc, g_zoom_factor);
		loc = glGetUniformLocation(gl_program->program, "view_decal_x");
		glUniform1f(loc, g_view_decal_x);
		loc = glGetUniformLocation(gl_program->program, "view_decal_y");
		glUniform1f(loc, g_view_decal_y);
		loc = glGetUniformLocation(gl_program->program, "mouse_position_x");
		glUniform1f(loc, g_mouse_position_x);
		loc = glGetUniformLocation(gl_program->program, "mouse_position_y");
		glUniform1f(loc, g_mouse_position_y);
		loc = glGetUniformLocation(gl_program->program, "time");
		glUniform1f(loc, glfwGetTime());

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		time_delta = glfwGetTime() - tmp_time;
		if (i % 50 == 0)
			set_window_title_with_time(window, time_delta);
		tmp_time = glfwGetTime();
		if (!g_particles_locked)
		{
			if (!(update_kernel_data_func(cl_program, update_kernel_data, data_buffer, time_delta,
				g_gravity_strength, g_center_gravity_x, g_center_gravity_y, nb_particles)))
			{
				printf("could not update kernel data\n");
				exit = 1;
			}
			if (!exit && !(update_particles_positions(cl_program, update_kernel,
				cl_buffer, nb_particles, data_buffer, time_delta)))
			{
				printf("could not update particles position. Exiting...\n");
				exit = 1;
			}
		}

		draw_gl_buffer(gl_program, gl_buffer, nb_particles);

		glfwSwapBuffers(window->win);
		if (!exit && glfwWindowShouldClose(window->win))
			exit = 1;
		i++;
	}
	clReleaseKernel(*update_kernel);
	clReleaseKernel(*set_kernel);
	finalize_cl_program(cl_program);
}

int		main(void)
{
	t_window			window;
	t_cl_program		cl_program;
	t_cl_buffer			cl_buffer;
	t_gl_program		gl_program;
	t_gl_buffer			gl_buffer;
	t_cl_buffer			data_buffer;
	cl_kernel			update_kernel;
	cl_kernel			set_kernel;
	cl_kernel			update_kernel_data;
	GLint				loc;
	unsigned int		nb_particles;
	size_t				file_size;
	char				*source_str;

	g_screen_width = 1800;
	g_screen_height = 1350;
	g_zoom_factor = 0.5;
	g_gravity_strength = 1.0;
	g_center_gravity_x = 0.0;
	g_center_gravity_y = 0.0;
	g_view_decal_x = 0.0;
	g_view_decal_y = 0.0;
	g_center_gravity_lock = 0;
	g_center_gravity_activated = 1;
	g_particles_locked = 1;
	nb_particles = 7000000;

	if (!(init_opengl(g_screen_width, g_screen_height, "60 fps", &window)))
		return (0);

	if (!(make_gl_program("shaders/vertex.vs", "shaders/fragment.fs", &gl_program)))
		return (0);
	if (!(make_gl_buffer(nb_particles, &gl_buffer)))
		return (0);

	glUseProgram(gl_program.program);
	loc = glGetUniformLocation(gl_program.program, "screen_ratio");
	glUniform1f(loc, (float)(g_screen_width / g_screen_height));

	if (!(source_str = get_file_source("hello.cl", &file_size)))
		return (0);
	if (!(make_cl_program(source_str, file_size, &cl_program)))
		return (0);
	if (!(make_kernel(&cl_program, "calculate_particles_position", &update_kernel)))
		return (0);
	//if (!(make_kernel(&cl_program, "set_particles_values", &set_kernel)))
	//	return (0);
	if (!(make_kernel(&cl_program, "set_particles_values_with_initial_velocity", &set_kernel)))
		return (0);
	if (!(make_kernel(&cl_program, "update_kernel_data", &update_kernel_data)))
		return (0);
	
	free(source_str);
	if (!(make_cl_buffer(&cl_program, &gl_buffer, &cl_buffer)))
		return (0);
	if (!(make_raw_cl_buffer(&cl_program, &data_buffer)))
		return (0);

	main_loop(&window, &cl_program, &cl_buffer, &gl_program, &gl_buffer,
									&update_kernel, &set_kernel, &update_kernel_data, &data_buffer, nb_particles); 
	return (0);
}