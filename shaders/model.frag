#version 330 core
in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;

out vec4 fragColor;

uniform sampler2D diffuse_map;

void main()
{
	fragColor = texture(diffuse_map,TexCoords);
}