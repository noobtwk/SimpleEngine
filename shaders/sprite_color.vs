#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 mvp_Matrix;

void main()
{
gl_Position =	mvp_Matrix * vec4(position,1.0f);
}