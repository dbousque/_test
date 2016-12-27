#version 330 core

in vec2 TextCoords;
in vec3 NormalVec;
in vec3 FragPos;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform vec3 ambientColor;
uniform vec3 cameraPos;
uniform vec3 lightColor1;
uniform vec3 lightPos1;

void main()
{
	vec3 objColor = vec3(0.8, 0.8, 0.8);

	vec3 norm = normalize(NormalVec);

	vec3 lightDir = normalize(lightPos1 - FragPos);
	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = lightColor1 * diff;
	float specularStrength = 1.0f;
	vec3 cameraDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(cameraDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor1;
	vec3 resLight1 = diffuse + specular;

	vec3 totLight = resLight1 + ambientColor;

	color = vec4(objColor * totLight, 1.0);// * texture(ourTexture1, TextCoords);
	//color = mix(texture(ourTexture1, TextCoords), texture(ourTexture2, TextCoords), 1.0);
}
