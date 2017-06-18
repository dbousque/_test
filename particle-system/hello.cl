

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
		float time_delta,
		float gravity_strength,
		float center_gravity_x,
		float center_gravity_y,
		char center_gravity_activated,
		__global t_particle *particles)
{
	int				i;
	float			gravity_vector_x;
	float			gravity_vector_y;
	float			distance_from_center;

	i = get_global_id(0);
	if (center_gravity_activated)
	{
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
		gravity_vector_x *= gravity_strength;
		gravity_vector_y *= gravity_strength;
		/*if (particles[i].velocity_x >= 1.4)
			particles[i].velocity_x = 1.4;
		if (particles[i].velocity_y >= 1.4)
			particles[i].velocity_y = 1.4;*/
		particles[i].velocity_x += gravity_vector_x * time_delta;
		particles[i].velocity_y += gravity_vector_y * time_delta;
	}
	particles[i].velocity_x *= 0.9985;
	particles[i].velocity_y *= 0.9985;
	particles[i].x += particles[i].velocity_x * time_delta;
	particles[i].y += particles[i].velocity_y * time_delta;
}