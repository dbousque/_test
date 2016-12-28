#version 330 core

in vec2 TextCoords;
in vec3 NormalVec;
in vec3 FragPos;
in vec3 Position;

out vec4 color;

uniform sampler2D ourTexture1;
uniform vec3 ambientColor;
uniform vec3 cameraPos;
uniform float textureStrength;

uniform int nbLights;

uniform vec3 lightColor1;
uniform vec3 lightPos1;
uniform vec3 ambientColor1;

uniform vec3 lightColor2;
uniform vec3 lightPos2;
uniform vec3 ambientColor2;

uniform vec3 lightColor3;
uniform vec3 lightPos3;
uniform vec3 ambientColor3;

uniform vec3 lightColor4;
uniform vec3 lightPos4;
uniform vec3 ambientColor4;

uniform vec3 lightColor5;
uniform vec3 lightPos5;
uniform vec3 ambientColor5;

uniform vec3 lightColor6;
uniform vec3 lightPos6;
uniform vec3 ambientColor6;

uniform vec3 lightColor7;
uniform vec3 lightPos7;
uniform vec3 ambientColor7;

uniform vec3 lightColor8;
uniform vec3 lightPos8;
uniform vec3 ambientColor8;

uniform vec3 lightColor9;
uniform vec3 lightPos9;
uniform vec3 ambientColor9;

uniform vec3 lightColor10;
uniform vec3 lightPos10;
uniform vec3 ambientColor10;

void	getNLightColor(in int n, out vec3 lightColorN)
{
	if (n == 1)
		lightColorN = lightColor1;
	else if (n == 2)
		lightColorN = lightColor2;
	else if (n == 3)
		lightColorN = lightColor3;
	else if (n == 4)
		lightColorN = lightColor4;
	else if (n == 5)
		lightColorN = lightColor5;
	else if (n == 6)
		lightColorN = lightColor6;
	else if (n == 7)
		lightColorN = lightColor7;
	else if (n == 8)
		lightColorN = lightColor8;
	else if (n == 9)
		lightColorN = lightColor9;
	else if (n == 10)
		lightColorN = lightColor10;
}

void	getNLightPos(in int n, out vec3 lightPosN)
{
	if (n == 1)
		lightPosN = lightPos1;
	else if (n == 2)
		lightPosN = lightPos2;
	else if (n == 3)
		lightPosN = lightPos3;
	else if (n == 4)
		lightPosN = lightPos4;
	else if (n == 5)
		lightPosN = lightPos5;
	else if (n == 6)
		lightPosN = lightPos6;
	else if (n == 7)
		lightPosN = lightPos7;
	else if (n == 8)
		lightPosN = lightPos8;
	else if (n == 9)
		lightPosN = lightPos9;
	else if (n == 10)
		lightPosN = lightPos10;
}

void	getNAmbientColor(in int n, out vec3 ambientColorN)
{
	if (n == 1)
		ambientColorN = ambientColor1;
	else if (n == 2)
		ambientColorN = ambientColor2;
	else if (n == 3)
		ambientColorN = ambientColor3;
	else if (n == 4)
		ambientColorN = ambientColor4;
	else if (n == 5)
		ambientColorN = ambientColor5;
	else if (n == 6)
		ambientColorN = ambientColor6;
	else if (n == 7)
		ambientColorN = ambientColor7;
	else if (n == 8)
		ambientColorN = ambientColor8;
	else if (n == 9)
		ambientColorN = ambientColor9;
	else if (n == 10)
		ambientColorN = ambientColor10;
}

void	getNLightColor(inout int n, inout vec3 norm, inout vec3 cameraDir, inout float specularStrength, inout vec3 resColor)
{
	vec3 lightPos;
	vec3 lightColor;
	vec3 ambientColor;

	getNLightPos(n, lightPos);
	getNLightColor(n, lightColor);
	getNAmbientColor(n, ambientColor);

	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = lightColor * diff;
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(cameraDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	resColor = diffuse + specular + ambientColor;
}

void	main()
{
	vec3 objColor = vec3(0.8, 0.8, 0.8);
	vec3 norm = normalize(NormalVec);
	float specularStrength = 3.0f;
	vec3 cameraDir = normalize(cameraPos - FragPos);
	vec3 totLight = vec3(0.0, 0.0, 0.0);
	vec3 tmpColor;

	for (int i = 1; i <= nbLights; i++)
	{
		getNLightColor(i, norm, cameraDir, specularStrength, tmpColor);
		totLight += tmpColor;
	}

	color = vec4(objColor * totLight, 1.0) * (1.0 - textureStrength);
	color += texture(ourTexture1, TextCoords) * vec4(totLight, 1.0) * textureStrength;
	//color = vec4(objColor * totLight, 1.0) * texture(ourTexture1, vec2(Position.x + Position.z, Position.y + Position.z));
}

/*void	main()
{
	vec3 objColor = vec3(0.8, 0.8, 0.8);

	vec3 norm = normalize(NormalVec);


	vec3 lightDir = normalize(lightPos1 - FragPos);
	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = lightColor1 * diff;
	float specularStrength = 3.0f;
	vec3 cameraDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(cameraDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor1;
	vec3 resLight1 = diffuse + specular + ambientColor1;

	vec3 totLight = resLight1;

	color = vec4(objColor * totLight, 1.0) * texture(ourTexture1, TextCoords);
	//color = mix(texture(ourTexture1, TextCoords), texture(ourTexture2, TextCoords), 1.0);
}*/
