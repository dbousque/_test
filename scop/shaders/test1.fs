#version 330 core

in vec2 TextCoords;
in vec3 NormalVec;
in vec3 FragPos;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform vec3 ambientColor;
uniform vec3 lightColor1;
uniform vec3 lightPos1;

void main()
{
	vec3 norm = normalize(NormalVec);
	vec3 lightDir = normalize(lightPos1 - FragPos);
	float diff = max(dot(lightDir, norm), 0.0);
	vec3 lightResColor1 = lightColor1 * diff + ambientColor;
	color = vec4(vec3(0.8, 0.8, 0.8) * lightResColor1, 1.0);
	//color = mix(texture(ourTexture1, TextCoords), texture(ourTexture2, TextCoords), 1.0);
}
