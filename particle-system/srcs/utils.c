

#include "particle_system.h"

char	parse_params(int argc, char **argv, unsigned int *nb_particles, char *mode)
{
	int		res;

	if (argc <= 1)
		return (1);
	res = atoi(argv[1]);
	if (res < 0)
		res = 0;
	*nb_particles = (unsigned int)res;
	if (argc <= 2)
		return (1);
	if (argv[2][0] == 's' && argv[2][1] == 'q' && argv[2][2] == 'u' && argv[2][3] == 'a'
				&& argv[2][4] == 'r' && argv[2][5] == 'e' && argv[2][6] == '\0')
	{
		*mode = 2;
	}
	if (argv[2][0] == 'c' && argv[2][1] == 'i' && argv[2][2] == 'r' && argv[2][3] == 'c'
				&& argv[2][4] == 'l' && argv[2][5] == 'e' && argv[2][6] == '\0')
	{
		*mode = 3;
	}
	if (argc <= 3)
		return (1);
	res = atoi(argv[3]);
	if (res < 200 || res > 2560)
		res = 1800;
	g_screen_width = res;
	if (argc <= 4)
		return (1);
	res = atoi(argv[4]);
	if (res < 200 || res > 2560)
		res = 1350;
	g_screen_height = res;
	return (1);
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


char	*get_file_source(char *filename, size_t *size)
{
	FILE			*fp;
	char			*res;
	struct stat		statbuf;

	fp = fopen(filename, "r");
	if (!fp)
	{
		printf("Failed to load %s.\n", filename);
		return (NULL);
	}
	stat(filename, &statbuf);
	if (!S_ISREG(statbuf.st_mode))
	{
		printf("Failed to load %s, not a regular file.\n", filename);
		return (NULL);
	}
	if (statbuf.st_size >= FILE_MAX_SIZE)
	{
		printf("Failed to load %s, file too big.\n", filename);
		return (NULL);
	}
	if (!(res = (char*)malloc(sizeof(char) * (statbuf.st_size + 1))))
	{
		printf("malloc error\n");
		return (NULL);
	}
	*size = statbuf.st_size;
	fread(res, sizeof(char), statbuf.st_size, fp);
	fclose(fp);
	res[*size] = '\0';
	return (res);
}