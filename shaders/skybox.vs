#version 330 core
layout (location = 0) in vec3 position;

out vec3 TexCoords;
uniform mat4 mvp_Matrix;

void main()
{
	vec4 pos = mvp_Matrix* vec4(position,1.0f);
	gl_Position = vec4(pos.x,pos.y,pos.w,pos.w);
	TexCoords = position;
}