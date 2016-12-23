#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textCoords;
layout (location = 2) in vec3 normalVec;

out vec2 TextCoords;
out vec3 NormalVec;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 tmp = projection * view * model * vec4(position, 1.0);
	gl_Position = vec4(tmp.x, tmp.y, -tmp.z, tmp.w);
	TextCoords = vec2(textCoords.x, 1.0 - textCoords.y);
	NormalVec = normalVec;
}
