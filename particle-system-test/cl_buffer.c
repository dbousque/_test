

#include "particle_system.h"

void	finalize_buffer(t_cl_buffer *buffer)
{
	clReleaseMemObject(buffer->buffer);
}

char	make_raw_cl_buffer(t_cl_program *program, t_cl_buffer *res)
{
	cl_int ret;

	res->buffer = NULL;
	res->buffer = clCreateBuffer(program->context, CL_MEM_READ_WRITE, sizeof(t_kernel_data), NULL, &ret);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(program, "clCreateBuffer", ret));
	return (1);

}

char	make_cl_buffer(t_cl_program *program, t_gl_buffer *gl_buffer,
															t_cl_buffer *res)
{
	cl_int ret;

	res->buffer = NULL;
	res->buffer = clCreateFromGLBuffer(program->context, CL_MEM_READ_WRITE,
														gl_buffer->vbo, &ret);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(program, "clCreateFromGLBuffer", ret));
	return (1);
}