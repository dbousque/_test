

typedef struct	s_particle
{
	float		mass;
	float		x;
	float		y;
	float		velocity_x;
	float		velocity_y;
}				t_particle;

__kernel void set_particles_values(unsigned int nb_particles, __global t_particle *particles)
{
	unsigned int	i;

	i = 0;
	while (i < nb_particles)
	{
		particles[i].mass = 1.0;
		particles[i].x = ((float)i) / ((float)nb_particles);
		particles[i].y = ((float)i) / ((float)nb_particles);
		particles[i].velocity_x = 0.0;
		particles[i].velocity_y = 0.0;
		i++;
	}
}

__kernel void set_particles_values_with_initial_velocity(unsigned int nb_particles, __global t_particle *particles)
{
	unsigned int	i;

	ulong seed = 56 + get_global_id(1);
	seed = (seed * 0x5DEECE66DL + 0xBL) & ((1L << 48) - 1);
	uint result = seed >> 16;
	i = 0;
	while (i < nb_particles)
	{
		particles[i].mass = 1.0;
		particles[i].x = ((float)i) / ((float)nb_particles);
		particles[i].y = ((float)i) / ((float)nb_particles);
		// generate random values for velocity
		particles[i].velocity_x = (float)((seed >> 16) % 1000) / 1000.0;
		particles[i].velocity_y = (float)((seed >> 16) % 1000) / 1000.0;
		i++;
	}
}

__kernel void calculate_particles_position(
		float time_delta,
		float center_gravity_mass,
		float center_gravity_x,
		float center_gravity_y,
		unsigned int nb_particles,
		__global t_particle *particles)
{
	unsigned int	i;
	float			gravity_force;
	float			gravity_vector_x;
	float			gravity_vector_y;
	float			distance_from_center;

	i = 0;
	while (i < nb_particles)
	{
		gravity_force = 0.05;
		gravity_vector_x = center_gravity_x - particles[i].x;
		gravity_vector_y = center_gravity_y - particles[i].y;
		distance_from_center = sqrt((gravity_vector_x * gravity_vector_x) + (gravity_vector_y * gravity_vector_y));
		if (fabs(gravity_vector_x) > fabs(gravity_vector_y))
		{
			gravity_vector_y = gravity_vector_y / fabs(gravity_vector_x);
			gravity_vector_x = gravity_vector_x >= 0.0 ? 1.0 : -1.0;
		}
		else
		{
			gravity_vector_y = gravity_vector_y >= 0.0 ? 1.0 : -1.0;
			gravity_vector_x = gravity_vector_x / fabs(gravity_vector_y);
		}
		particles[i].velocity_x += gravity_vector_x * time_delta;
		particles[i].velocity_y += gravity_vector_y * time_delta;
		particles[i].x += particles[i].velocity_x * time_delta;
		particles[i].y += particles[i].velocity_y * time_delta;
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