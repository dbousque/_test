

typedef struct	s_particle
{
	float		x;
	float		y;
}				t_particle;

__kernel void calculate_particles_position(float center_gravity_x, float center_gravity_y,
								unsigned int nb_particles, __global t_particle *particles)
{
	unsigned int	i;

	i = 0;
	while (i < nb_particles)
	{
		particles[i].x = 0.4;
		particles[i].y = 0.7;
		i++;
	}
	/*string[0] = 'H';
	string[1] = 'e';
	string[2] = 'l';
	string[3] = 'l';
	string[4] = 'o';
	string[5] = ',';
	string[6] = ' ';
	string[7] = 'W';
	string[8] = 'o';
	string[9] = 'r';
	string[10] = 'l';
	string[11] = 'd';
	string[12] = '!';
	string[13] = '\0';*/
}