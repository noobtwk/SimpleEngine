#pragma once
#ifndef VEC3_H
#define VEC3_H

#include"vec2.h"
class vec3
{
public:
	float x, y, z;
	vec3();
	vec3(const vec3 &v);
	vec3(float nx, float ny, float nz);
	vec3(const vec2 &v, float a);

	bool operator ==(const vec3 &v) const;
	bool operator !=(const vec3 &v) const;
	vec3 &operator =(const vec3 &v);
	vec3 operator -() const;
	vec3 operator +(const vec3 &v) const;
	vec3 operator -(const vec3 &v) const;
	vec3 operator *(float a) const;
	vec3 operator /(float a) const;
	vec3 &operator +=(const vec3 &v);
	vec3 &operator -=(const vec3 &v);
	vec3 &operator +=(float a) ;
	vec3 &operator -=(float a) ;
	vec3 &operator *=(float a);
	vec3 &operator /=(float a);


	void normalize();
	float distance(const vec3  &a, const vec3 &b);
	float dot(const vec3 &a, const vec3 &b);
	static vec3 cross(const vec3 &a, const vec3 &b);


private:

};


#endif // !VEC3_H
