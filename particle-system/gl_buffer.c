

#include "particle_system.h"

void	draw_gl_buffer(t_gl_program *gl_program, t_gl_buffer *buffer,
													unsigned int nb_particles)
{
	glUseProgram(gl_program->program);
	glBindVertexArray(buffer->vao);
	glDrawArrays(GL_POINTS, 0, nb_particles);
	glBindVertexArray(0);
}

char	make_gl_buffer(int nb_particles, t_gl_buffer *buffer)
{
	glGenVertexArrays(1, &(buffer->vao));
	glBindVertexArray(buffer->vao);
	glGenBuffers(1, &(buffer->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, buffer->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * 2 * nb_particles,
													NULL, GL_STATIC_DRAW);
	
	// 2 for vec2 input (x,y) for particles
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	return (1);
}