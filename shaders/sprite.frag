#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture1;
uniform vec3 Color;

void main()
{
	vec4 color1 = texture(texture1,TexCoords) * vec4(Color,1.0);
	if(color1.a<0.1)
		discard;
	color = color1;
}