

#include "wolf3d.h"

void	draw_object(t_wolf3d *wolf3d, int pixel_x, t_ray_result *ray_res)
{
	float		height_at_zero;
	float		full_screen_point;
	float		block_height;
	int			block_until;
	float		from[2];

	height_at_zero = 1.3;
	full_screen_point = 1.0;
	block_height = height_at_zero / (ray_res->distance / full_screen_point);
	block_until = (wolf3d->window.height / 2) * block_height;
	from[0] = ray_res->x;
	from[1] = ray_res->y;
	send_ray_in_dir(wolf3d, ray_res->direction, pixel_x, from);
	draw_texture(wolf3d, pixel_x, ray_res, block_until);
}

float	angle_of_vectors(float vec1[2], float vec2[2])
{
	float	mag_vec1;
	float	mag_vec2;
	float	dot_product;
	float	param;

	mag_vec1 = sqrt((vec1[0] * vec1[0]) + (vec1[1] * vec1[1]));
	mag_vec2 = sqrt((vec2[0] * vec2[0]) + (vec2[1] * vec2[1]));
	dot_product = (vec1[0] * vec2[0]) + (vec1[1] * vec2[1]);
	param = dot_product / (mag_vec1 * mag_vec2);
	if (param > 1.0)
		param = 1.0;
	if (param < -1.0)
		param = -1.0;
	return (acosf(param));
}

char	vector_on_the_left(float vec1[2], float vec2[2])
{
	float	angle1;
	float	angle2;
	float	diff;
	float	horizon[2];

	horizon[0] = 1.0;
	horizon[1] = 0.0;
	angle1 = RAD_TO_DEG(angle_of_vectors(horizon, vec1));
	if (vec1[1] < 0.0)
		angle1 = -angle1;
	angle2 = RAD_TO_DEG(angle_of_vectors(horizon, vec2));
	if (vec2[1] < 0.0)
		angle2 = -angle2;
	diff = angle1 - angle2;
	if (diff < -180.0)
		diff += 360.0;
	if (diff > 180.0)
		diff -= 360.0;
	if (diff > 0.0)
		return (1);
	return (0);
}

void	render_object(t_wolf3d *wolf3d, int pixel_x, t_ray_result *ray_res)
{
	float	block_center_x;
	float	block_center_y;
	float	decal;
	float	vector[2];
	float	center_vector[2];

	block_center_x = (float)ray_res->block_x + 0.5;
	block_center_y = (float)ray_res->block_y + 0.5;
	ray_res->distance =
		fabsf(wolf3d->player.x - block_center_x) *
			fabsf(wolf3d->player.x - block_center_x) +
		fabsf(wolf3d->player.y - block_center_y) *
			fabsf(wolf3d->player.y - block_center_y);
	ray_res->distance = sqrtf(ray_res->distance);
	vector[0] = cosf(DEG_TO_RAD(ray_res->direction));
	vector[1] = sinf(DEG_TO_RAD(ray_res->direction));
	normalize_decals(&(vector[0]), &(vector[1]));
	center_vector[0] = block_center_x - wolf3d->player.x;
	center_vector[1] = block_center_y - wolf3d->player.y;
	normalize_decals(&(center_vector[0]), &(center_vector[1]));
	decal =(ray_res->distance * sinf(angle_of_vectors(vector, center_vector)))
		/ sinf(DEG_TO_RAD(90.0));
	decal = vector_on_the_left(vector, center_vector) ? decal : -decal;
	ray_res->decal_in_face = ((decal * 1.7) + 1) / 2.0;
	draw_object(wolf3d, pixel_x, ray_res);
}

void	render_ray(t_wolf3d *wolf3d, int pixel_x, t_ray_result *ray_res)
{
	if (wolf3d->opts.debug_mode)
		return (render_debug_ray(wolf3d, pixel_x, ray_res));
	if (ray_res->block && ray_res->block->is_object)
		return (render_object(wolf3d, pixel_x, ray_res));
	ray_res->distance =
	fabsf(wolf3d->player.x - ray_res->x) *
		fabsf(wolf3d->player.x - ray_res->x) +
	fabsf(wolf3d->player.y - ray_res->y) *
		fabsf(wolf3d->player.y - ray_res->y);
	ray_res->distance = sqrtf(ray_res->distance);
	if (ray_res->block)
	{
		if (ray_res->face == 0)
			ray_res->decal_in_face = ((int)ray_res->x + 1) - ray_res->x;
		else if (ray_res->face == 1)
			ray_res->decal_in_face = ((int)ray_res->y + 1) - ray_res->y;
		else if (ray_res->face == 2)
			ray_res->decal_in_face = ray_res->x - (int)ray_res->x;
		else
			ray_res->decal_in_face = ray_res->y - (int)ray_res->y;
	}
	draw_column(wolf3d, pixel_x, ray_res);
}