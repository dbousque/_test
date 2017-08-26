

typedef struct	s_particle
{
	float		mass;
	float		x;
	float		y;
	float		velocity_x;
	float		velocity_y;
}				t_particle;

typedef struct			s_kernel_data
{
	float				time_delta;
	float				gravity_strength;
	float				center_gravity_x;
	float				center_gravity_y;
	char				center_gravity_activated;
	unsigned int		nb_particles;
	unsigned int		batch_size;
}						t_kernel_data;

__kernel void update_kernel_data(
	float time_delta,
	float gravity_strength,
	float center_gravity_x,
	float center_gravity_y,
	char center_gravity_activated,
	unsigned int nb_particles,
	unsigned int batch_size,
	__global t_kernel_data *data)
{
	data->time_delta = time_delta;
	data->gravity_strength = gravity_strength;
	data->center_gravity_x = center_gravity_x;
	data->center_gravity_y = center_gravity_y;
	data->center_gravity_activated = center_gravity_activated;
	data->nb_particles = nb_particles;
	data->batch_size = batch_size;
}

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
		 const t_kernel_data data,
		__global t_particle *particles)
{
	__local float			gravity_vector_x;
	__local float			gravity_vector_y;
	__local float			distance_from_center;
	__local int				id;
	__local t_particle		particle;
	//__local t_kernel_data	data;

	//data = *ori_data;
	id = get_global_id(0);
	int i = id * data.batch_size;
	while (i < id * data.batch_size + data.batch_size && i < data.nb_particles)
	{
		particle = particles[i];
		if (!data.center_gravity_activated)
		{
			particle.velocity_x *= 0.997;
			particle.velocity_y *= 0.997;
			particle.x += particle.velocity_x * data.time_delta;
			particle.y += particle.velocity_y * data.time_delta;
			particles[i] = particle;
			i++;
			continue ;
		}
		gravity_vector_x = data.center_gravity_x - particle.x;
		gravity_vector_y = data.center_gravity_y - particle.y;
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
		gravity_vector_x *= data.gravity_strength;
		gravity_vector_y *= data.gravity_strength;

		particle.velocity_x += gravity_vector_x * data.time_delta;
		particle.velocity_y += gravity_vector_y * data.time_delta;
		particle.x += particle.velocity_x * data.time_delta;
		particle.y += particle.velocity_y * data.time_delta;
		particles[i] = particle;
		i++;
	}
}