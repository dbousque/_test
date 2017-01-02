

#include "myopengl.h"

void	set_lights(t_list *objs, t_list *lights, float texture_strength,
														float colors_strength)
{
	size_t		i;
	size_t		x;
	t_globj		*obj;
	t_light		*light;
	GLint		loc;
	char		*tmp;
	char		*x_str;

	i = 0;
	while (i < objs->len)
	{
		obj = ((t_globj**)objs->elts)[i];
		glUseProgram(obj->shader->program);
		loc = glGetUniformLocation(obj->shader->program, "cameraPos");
		glUniform3f(loc, g_cam.x, g_cam.y, g_cam.z);
		loc = glGetUniformLocation(obj->shader->program, "nbLights");
		glUniform1i(loc, (int)lights->len);
		loc = glGetUniformLocation(obj->shader->program, "textureStrength");
		glUniform1f(loc, texture_strength);
		loc = glGetUniformLocation(obj->shader->program, "colorsStrength");
		glUniform1f(loc, colors_strength);
		x = 0;
		while (x < lights->len)
		{
			light = ((t_light**)lights->elts)[x];
			x_str = ft_itoa(x + 1);
			tmp = ft_strconcat("lightColor", x_str);
			loc = glGetUniformLocation(obj->shader->program, tmp);
			glUniform3f(loc, light->r, light->g, light->b);
			free(tmp);
			tmp = ft_strconcat("lightPos", x_str);
			loc = glGetUniformLocation(obj->shader->program, tmp);
			glUniform3f(loc, light->obj->x, light->obj->y, light->obj->z);
			free(tmp);
			tmp = ft_strconcat("ambientColor", x_str);
			loc = glGetUniformLocation(obj->shader->program, tmp);
			glUniform3f(loc, light->r * light->ambient_strength,
					light->g * light->ambient_strength, light->b * light->ambient_strength);
			free(tmp);
			free(x_str);
			x++;
		}
		i++;
	}
}

void	draw_objects(t_list *objs, t_mat *view, t_mat *projection)
{
	size_t				i;
	t_mat				*model;
	t_mat				*scal;
	t_mat				*rot;
	t_mat				*trans;
	t_mat				*transpInv;
	t_mat				*inv;
	t_shader_program	*shader;
	GLuint				loc;
	t_globj				*obj;

	i = 0;
	while (i < objs->len)
	{
		obj = ((t_globj**)objs->elts)[i];
		shader = obj->shader;
		glUseProgram(shader->program);
		if (i == 0)
		{
			trans = translate(new_vec3(obj->x, obj->y, obj->z));
			scal = scale(new_vec3(g_conf.obj_scale, g_conf.obj_scale, g_conf.obj_scale));
			rot = rotate(new_vec3(0.0, 0.0, deg_to_rad((GLfloat)glfwGetTime() * 15.0f)));
			model = mat_mult(scal, trans);
			model = mat_mult(model, rot);
		}
		else
			model = translate(new_vec3(obj->x, obj->y, obj->z));
		//view = translate(new_vec3(0.0, 0.0, -3.0 + (mixVal * 4)));
		//model = new_mat4();
		inv = invert(model);
		transpInv = transpose(inv);
		loc = glGetUniformLocation(shader->program, "transpInv");
		glUniformMatrix4fv(loc, 1, GL_TRUE, transpInv->elts);

		loc = glGetUniformLocation(shader->program, "model");
		glUniformMatrix4fv(loc, 1, GL_TRUE, model->elts);
		loc = glGetUniformLocation(shader->program, "view");
		glUniformMatrix4fv(loc, 1, GL_TRUE, view->elts);
		loc = glGetUniformLocation(shader->program, "projection");
		glUniformMatrix4fv(loc, 1, GL_TRUE, projection->elts);
		draw_object(shader, ((t_globj**)objs->elts)[i]);
		i++;
	}
}

void	draw_lights(t_list *lights, t_mat *view, t_mat *projection)
{
	size_t				i;
	t_shader_program	*shader;
	GLuint				loc;
	t_light				*light;
	t_mat				*model;

	i = 0;
	while (i < lights->len)
	{
		light = ((t_light**)lights->elts)[i];
		shader = light->obj->shader;

		glUseProgram(shader->program);

		loc = glGetUniformLocation(shader->program, "lightColor");
		glUniform3f(loc, light->r, light->g, light->b);

		model = translate(new_vec3(light->obj->x, light->obj->y, light->obj->z));

		loc = glGetUniformLocation(shader->program, "model");
		glUniformMatrix4fv(loc, 1, GL_TRUE, model->elts);

		loc = glGetUniformLocation(shader->program, "view");
		glUniformMatrix4fv(loc, 1, GL_TRUE, view->elts);

		loc = glGetUniformLocation(shader->program, "projection");
		glUniformMatrix4fv(loc, 1, GL_TRUE, projection->elts);

		draw_object(shader, light->obj);
		i++;
	}
}