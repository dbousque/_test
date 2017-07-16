

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

__kernel void set_particles_values_with_initial_velocity(unsigned int nb_particles, char mode, __global t_particle *particles)
{
	unsigned int	i;
	unsigned int	y;
	unsigned int	square_size;

	i = 0;
	y = 0;
	square_size = (unsigned int)sqrt((float)nb_particles);
	while (i < nb_particles)
	{
		if ((i + 1) % square_size == 0)
		{
			y++;
		}
		particles[i].mass = 1.0;
		if (mode == 1)
		{
			// line
			particles[i].x = ((float)i) / ((float)nb_particles);
			particles[i].y = ((float)i) / ((float)nb_particles);
		}
		else if (mode == 2)
		{
			// square
			particles[i].x = (float)(i % square_size) / (square_size / 2) - 1.0;
			particles[i].y = (float)(y % square_size) / (square_size / 2) - 1.0;
		}
		else if (mode == 3)
		{
			// circle
			particles[i].x = (float)(i % square_size) / (square_size / 2) - 1.0;
			particles[i].y = (float)(y % square_size) / (square_size / 2) - 1.0;
			float limit = sqrt(1.0 - pow(fabs(particles[i].y), 2));
			if (fabs(particles[i].x) > fabs(limit))
			{
				particles[i].x = ((int)(particles[i].x * 100000.0) % (int)(limit * 100000.0)) / 100000.0;
			}
		}
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
		const float gravity_strength,
		const float center_gravity_x,
		const float center_gravity_y,
		const char center_gravity_activated,
		const int n,
		const unsigned int nb_particles,
		const char decay,
		const unsigned int batch_size,
		__global t_particle *ps)
{
	float			gravity_vector_x;
	float			gravity_vector_y;
	int				id;
	t_particle		p;

	id = get_global_id(0);
	int i = id * batch_size;
	while (i < id * batch_size + batch_size && i < nb_particles)
	{
		p = ps[i];
		if (!center_gravity_activated)
		{
			p.velocity_x *= 0.997;
			p.velocity_y *= 0.997;
			p.x += p.velocity_x * time_delta;
			p.y += p.velocity_y * time_delta;
			int x = 0;
			while (x < n) {
				ps[i + x] = p;
				x++;
			}
			i+=n;
			continue ;
		}
		gravity_vector_x = center_gravity_x - p.x;
		gravity_vector_y = center_gravity_y - p.y;
		//distance_from_center = sqrt((gravity_vector_x * gravity_vector_x) + (gravity_vector_y * gravity_vector_y));
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

		p.velocity_x += gravity_vector_x * time_delta;
		p.velocity_y += gravity_vector_y * time_delta;
		if (decay) {
			p.velocity_x *= 0.997;
			p.velocity_y *= 0.997;
		}
		p.x += p.velocity_x * time_delta;
		p.y += p.velocity_y * time_delta;
		int x = 0;
		while (x < n) {
			ps[i + x] = p;
			x++;
		}
		i+=n;
	}
}