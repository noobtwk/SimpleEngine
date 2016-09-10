#pragma once
#ifndef QUATERNION_H
#define QUATERNION_H
#include<math.h>
#include"vec3.h"
class Quaternion
{
public:
	float w, x, y, z;
	Quaternion();
	Quaternion(float W, float X, float Y, float Z);
	~Quaternion() {};

	Quaternion & operator =(const Quaternion &q);

	Quaternion operator -() const;

	void normalize();
	static Quaternion slerp(Quaternion q0,Quaternion q1,float t);
	void matrixToQua(vec3 Xaxis, vec3 Yaxis, vec3 Zaxis);
	void EulerToQua(vec3 Euler);
	void QuaToEuler(float *h, float *p, float *b);

private:

};

#endif // !QUATERNION_H
