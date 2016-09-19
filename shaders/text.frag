#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D texture1;
uniform vec3 Color;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(texture1, TexCoords).r);
    vec4 color1 = vec4(Color,1.0f)*sampled;
	//if(color1.a ==0.0)
	//	discard;
	color = color1;
}  