#version 330 core

uniform vec3 lightColor;
uniform float redStrength;
uniform float greenStrength;
uniform float blueStrength;

out vec4 color;

void	main()
{
	vec3 newlightColor = vec3(lightColor.r * redStrength, lightColor.g * greenStrength, lightColor.b * blueStrength);
	color = vec4(newlightColor, 1.0);
}