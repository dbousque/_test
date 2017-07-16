

#include "particle_system.h"

char	create_shader(GLchar const *shader_source, int mode, GLuint *shader)
{
	GLint	success;
	GLchar	info_log[512];

	*shader = glCreateShader(mode);
	glShaderSource(*shader, 1, &shader_source, NULL);
	glCompileShader(*shader);
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*shader, 512, NULL, info_log);
		printf("SHADER COMPILATION ERROR : %s\n", info_log);
		return (0);
	}
	return (1);
}

char	create_shaders(GLchar const *vs_content,
							GLchar const *fs_content, t_gl_program *program)
{
	if (!(create_shader(vs_content, GL_VERTEX_SHADER,
											&(program->vertex_shader))))
	{
		printf("could not compile vertex shader\n");
		return (0);
	}
	if (!(create_shader(fs_content, GL_FRAGMENT_SHADER,
										&(program->fragment_shader))))
	{
		printf("could not compile fragment shader\n");
		return (0);
	}
	return (1);
}

char	create_shaders_and_program(GLchar const *vs_content,
							GLchar const *fs_content, t_gl_program *program)
{
	GLint	success;
	GLchar	info_log[512];

	if (!(create_shaders(vs_content, fs_content, program)))
		return (0);
	program->program = glCreateProgram();
	glAttachShader(program->program, program->vertex_shader);
	glAttachShader(program->program, program->fragment_shader);
	glLinkProgram(program->program);
	glGetProgramiv(program->program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program->program, 512, NULL, info_log);
		printf("PROGRAM LINKING ERROR : %s\n", info_log);
		return (0);
	}
	glDeleteShader(program->vertex_shader);
	glDeleteShader(program->fragment_shader);
	return (1);
}

char	make_gl_program(char *vertex_shader_path,
							char *fragment_shader_path, t_gl_program *program)
{
	GLchar const	*vs_cont;
	GLchar const	*fs_content;
	size_t			size;

	vs_cont = get_file_source(vertex_shader_path, &size);
	if (!vs_cont)
	{
		printf("%s : invalid file\n", vertex_shader_path);
		return (0);
	}
	fs_content = get_file_source(fragment_shader_path, &size);
	if (!fs_content)
	{
		printf("%s : invalid file\n", fragment_shader_path);
		return (0);
	}
	return (create_shaders_and_program(vs_cont, fs_content, program));
}
