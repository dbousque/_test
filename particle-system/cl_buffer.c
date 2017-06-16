

#include "particle_system.h"

void	finalize_buffer(t_cl_buffer *buffer)
{
	clReleaseMemObject(buffer->buffer);
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