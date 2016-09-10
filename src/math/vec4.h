#pragma once
#ifndef VEC4_H
#define VEC4_H
#include"vec3.h"
class vec4
{
public:
	float x, y, z, w;
	vec4();
	vec4(const vec4 &v);
	vec4(float nx, float ny, float nz, float nw);
	vec4(const vec3 &v, float w);
private:

};


#endif // !VEC4_H
