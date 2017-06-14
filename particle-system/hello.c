

#include "particle_system.h"

char	*get_file_source(char *filename, size_t *size)
{
	FILE			*fp;
	char			*res;
	struct stat		statbuf;

	fp = fopen(filename, "r");
	if (!fp)
	{
		printf("Failed to load kernel.\n");
		return (NULL);
	}
	stat(filename, &statbuf);
	if (!S_ISREG(statbuf.st_mode))
	{
		printf("Failed to load kernel, not a regular file.\n");
		return (NULL);
	}
	if (statbuf.st_size >= FILE_MAX_SIZE)
	{
		printf("Failed to load kernel, file too big.\n");
		return (NULL);
	}
	if (!(res = (char*)malloc(sizeof(char) * statbuf.st_size)))
	{
		printf("malloc error\n");
		return (NULL);
	}
	*size = statbuf.st_size;
	fread(res, sizeof(char), statbuf.st_size, fp);
	fclose(fp);
	return (res);
}

char	cl_operation_failed(t_cl_program *program, char *msg, cl_int error_code)
{
	size_t	log_size;
	char	*log;
	cl_int	ret;

	printf("%s failed, error code : %d\n", msg, error_code);
	if (error_code == CL_BUILD_PROGRAM_FAILURE)
	{
		ret = clGetProgramBuildInfo(program->program, program->device_id,
									CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		if (ret != CL_SUCCESS)
			return (0);
		if (!(log = (char*)malloc(log_size)))
			return (0);
		ret = clGetProgramBuildInfo(program->program, program->device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
		if (ret != CL_SUCCESS)
		{
			free(log);
			return (0);
		}
		printf("build error : \n%s\n", log);
		free(log);
	}
	return (0);
}

void	init_cl_program_struct(t_cl_program *program)
{
	program->command_queue = NULL;
	program->context = NULL;
	program->program = NULL;
	program->kernel = NULL;
	program->device_id = NULL;
	program->platform_id = NULL;
}

char	make_cl_program(char *source_str, size_t file_size, char *kernel_name, t_cl_program *res)
{
	cl_uint		ret_num_devices;
	cl_uint		ret_num_platforms;
	cl_int		ret;

	init_cl_program_struct(res);
	ret = clGetPlatformIDs(1, &(res->platform_id), &ret_num_platforms);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(res, "clGetPlatformIDs", ret));
	ret = clGetDeviceIDs(res->platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &(res->device_id), &ret_num_devices);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(res, "clGetDeviceIDs", ret));
	res->context = clCreateContext(NULL, 1, &(res->device_id), NULL, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(res, "clCreateContext", ret));
	res->command_queue = clCreateCommandQueue(res->context, res->device_id, 0, &ret);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(res, "clCreateCommandQueue", ret));
	res->program = clCreateProgramWithSource(res->context, 1, (const char**)&source_str, &file_size, &ret);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(res, "clCreateProgramWithSource", ret));
	ret = clBuildProgram(res->program, 1, &(res->device_id), NULL, NULL, NULL);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(res, "clBuildProgram", ret));
	res->kernel = clCreateKernel(res->program, kernel_name, &ret);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(res, "clCreateKernel", ret));
	return (1);
}

char	make_cl_buffer(t_cl_program *program, size_t buffer_size, t_cl_buffer *res)
{
	cl_int ret;

	res->buffer = NULL;
	res->buffer = clCreateBuffer(program->context, CL_MEM_READ_WRITE, buffer_size, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(program, "clCreateBuffer", ret));
	return (1);
}

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

void	finalize_cl_program(t_cl_program *program)
{
	cl_int ret;

	ret = clFlush(program->command_queue);
	ret = clFinish(program->command_queue);
	ret = clReleaseKernel(program->kernel);
	ret = clReleaseProgram(program->program);
	ret = clReleaseCommandQueue(program->command_queue);
	ret = clReleaseContext(program->context);
}

void	finalize_buffer(t_cl_buffer *buffer)
{
	cl_int ret;

	ret = clReleaseMemObject(buffer->buffer);
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
	cl_int				ret;
	size_t				nb_particles;
	size_t				file_size;
	t_cl_program		cl_program;
	t_cl_buffer			cl_buffer;
	char				*source_str;

	nb_particles = 120;
	char string[sizeof(char) * nb_particles];

	if (!(source_str = get_file_source("hello.cl", &file_size)))
		return (0);
	if (!(make_cl_program(source_str, file_size, "calculate_particles_position", &cl_program)))
		return (0);
	free(source_str);
	if (!(make_cl_buffer(&cl_program, sizeof(char) * nb_particles, &cl_buffer)))
		return (0);
	void	*args[4];
	size_t	args_size[4];
	float center_gravity_x;
	float center_gravity_y;
	center_gravity_x = 12.4;
	center_gravity_y = 4.2;
	args[0] = &center_gravity_x;
	args[1] = &center_gravity_y;
	args[2] = &nb_particles;
	args[3] = &(cl_buffer.buffer);
	args_size[0] = sizeof(float);
	args_size[1] = sizeof(float);
	args_size[2] = sizeof(size_t);
	args_size[3] = sizeof(cl_mem);
	if (!(call_kernel_with_args(&cl_program, args, args_size, 4)))
		return (0);
	 
	/* Copy results from the memory buffer */
	ret = clEnqueueReadBuffer(cl_program.command_queue, cl_buffer.buffer, CL_TRUE, 0,
		sizeof(char) * nb_particles, string, 0, NULL, NULL);
	 
	/* Display Result */
	puts(string);

	init_opengl(800, 800, "salut title");

	finalize_buffer(&cl_buffer);
	finalize_cl_program(&cl_program);
 
	return 0;
}