#include "vec4.h"

vec4::vec4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{
}

vec4::vec4(const vec4 & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

vec4::vec4(float nx, float ny, float nz, float nw) :x(nx), y(ny), z(nz), w(nw)
{
}

vec4::vec4(const vec3 & v, float w)
{
	x = v.x;
	y = v.y;
	z = v.z;
	this->w = w;
}

