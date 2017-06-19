

#include "particle_system.h"

void	finalize_cl_program(t_cl_program *program)
{
	clFlush(program->command_queue);
	clFinish(program->command_queue);
	clReleaseProgram(program->program);
	clReleaseCommandQueue(program->command_queue);
	clReleaseContext(program->context);
}

void	init_cl_program_struct(t_cl_program *program)
{
	program->command_queue = NULL;
	program->context = NULL;
	program->program = NULL;
	program->device_id = NULL;
	program->platform_id = NULL;
}

char	make_kernel(t_cl_program *program, char *name, cl_kernel *kernel)
{
	cl_int		ret;

	*kernel = clCreateKernel(program->program, name, &ret);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(program, "clCreateKernel", ret));
	return (1);
}

char	make_cl_program(char *source_str, size_t file_size, t_cl_program *res)
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

	#if defined(__APPLE__)                                                                
		CGLContextObj     kCGLContext     = CGLGetCurrentContext();
		CGLShareGroupObj  kCGLShareGroup  = CGLGetShareGroup(kCGLContext);

		cl_context_properties props[] = {
			CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
			(cl_context_properties) kCGLShareGroup,
			0
		};
	#else
        cl_context_properties props[] = 
        {
            CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(), 
            CL_GLX_DISPLAY_KHR, (cl_context_properties)glXGetCurrentDisplay(), 
            CL_CONTEXT_PLATFORM, (cl_context_properties)res->platform_id, 
            0
        };
    #endif
    /*#else // Win32
        cl_context_properties props[] = 
        {
            CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(), 
            CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(), 
            CL_CONTEXT_PLATFORM, (cl_context_properties)res->platform_id, 
            0
        };
    #endif*/

	res->context = clCreateContext(props, 1, &(res->device_id), NULL, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(res, "clCreateContext", ret));
	printf("herre2\n");
	fflush(stdout);
	res->command_queue = clCreateCommandQueue(res->context, res->device_id, 0, &ret);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(res, "clCreateCommandQueue", ret));
	res->program = clCreateProgramWithSource(res->context, 1, (const char**)&source_str, &file_size, &ret);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(res, "clCreateProgramWithSource", ret));
	ret = clBuildProgram(res->program, 1, &(res->device_id), NULL, NULL, NULL);
	if (ret != CL_SUCCESS)
		return (cl_operation_failed(res, "clBuildProgram", ret));
	return (1);
}