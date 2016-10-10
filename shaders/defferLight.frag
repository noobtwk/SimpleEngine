#version 330 core
in vec2 TexCoords;

out vec4 FragColor;


uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gColor;
uniform sampler2D depthMap;

void main()
{
	vec3 FragPos = texture(gPosition,TexCoords).rgb;
	vec3 norm = texture(gNormal,TexCoords).rgb;
	vec3 color = texture(gColor,TexCoords).rgb;
	vec3 depth = texture(depthMap,TexCoords).rgb;
	
	FragColor = vec4(color,1.0f);
}