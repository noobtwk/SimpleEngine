#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoords;

uniform mat4 mvp_Matrix;

out vec2 TexCoords;

void main()
{
gl_Position =	mvp_Matrix * vec4(position,1.0f);
TexCoords = texcoords;
}
