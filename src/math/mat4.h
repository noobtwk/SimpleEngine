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
	void rotato(const Quaternion &Q);
	void rotato(float angle, vec3 axis);
	void translate(const vec3 &v);
	void scale(const vec3 &v);
	void perspective(float fovy,float aspect,float near,float far);
	void ortho(float left,float right,float bottom,float top,float near,float far);
	void frustum(float left, float right, float bottom, float top, float near, float far);
	mat4 transpose();
	mat4 inverse(bool *invertible);
	mat4 & operator =(const mat4 &n);
	mat4 operator *(const mat4 &m) const;
	vec4 operator *(const vec4 &v) const;
	float *data();


private:
	float val[16];
};

mat4 rotato(mat4 mat, const Quaternion &q);
mat4 translate(mat4 mat, const vec3 &v);
mat4 scale(mat4 mat, const vec3 &v);

#endif // !MAT_H
