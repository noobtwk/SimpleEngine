#pragma once
#ifndef MAT4_H
#define MAT4_H
#include"vec4.h"
#include"vec3.h"
#include"Quaternion.h"
class mat4
{
public:
	mat4();

	void idenity();
	void rotate(const Quaternion &Q);
	void rotate(float angle, vec3 axis);
	void translate(const vec3 &v);
	void scale(const vec3 &v);
	void perspective(float fovy,float aspect,float near,float far);
	void ortho(float left,float right,float bottom,float top,float near,float far);
	void frustum(float left, float right, float bottom, float top, float near, float far);
	mat4 transpose();
	mat4 inverse();
	mat4 & operator =(const mat4 &n);
	mat4 operator *(const mat4 &  other) const;
	vec4 operator *(const vec4 &v) const;
	
	float *data();
static mat4 rotate(mat4 mat, const Quaternion &q);
static mat4 translate(mat4 mat, const vec3 &v);
static mat4 scale(mat4 mat, const vec3 &v);

private:
	float val[16];
};



#endif // !MAT_H
