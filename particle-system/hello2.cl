

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

	i = 0;
	while (i < nb_particles)
	{
		particles[i].mass = 1.0;
		particles[i].x = ((float)i) / ((float)nb_particles);
		particles[i].y = ((float)i) / ((float)nb_particles);
		// generate random values for velocity
		uint seed = 42 + i;
		uint t = seed ^ (seed << 11);  
		uint result = 67 ^ (6518415 >> 19) ^ (t ^ (t >> 8));
		particles[i].velocity_x = ((float)(result % 10000)) / 100 / 50.0 - 1.0;
		particles[i].velocity_y = 0.0;
		i++;
	}
}

__kernel void calculate_particles_position(
		const float time_delta,
		const float center_gravity_x,
		const float center_gravity_y,
		const unsigned int nb_particles,
		const unsigned int batch_size,
		__global t_particle *particles)
{
	float			gravity_vector_x;
	float			gravity_vector_y;
	int				id;
	t_particle		particle;

	id = get_global_id(0);
	int i = id * batch_size;
	int limit = id * batch_size + batch_size;
	while (i < limit && i < nb_particles)
	{
		particle = particles[i];
		gravity_vector_x = center_gravity_x - particle.x;
		gravity_vector_y = center_gravity_y - particle.y;
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

		particle.velocity_x += gravity_vector_x * time_delta;
		particle.velocity_y += gravity_vector_y * time_delta;
		particle.x += particle.velocity_x * time_delta;
		particle.y += particle.velocity_y * time_delta;
		particles[i] = particle;
		particles[i + 1] = particle;
		particles[i + 2] = particle;
		particles[i + 3] = particle;
		particles[i + 4] = particle;
		i += 5;
	}
}