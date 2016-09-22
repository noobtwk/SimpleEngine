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
	static Quaternion slerp(Quaternion start, Quaternion end, float dt);
	void matrixToQua(vec3 Xaxis, vec3 Yaxis, vec3 Zaxis);
	void EulerToQua(vec3 Euler);
	void QuaToEuler(float *resultX, float *resultY, float *resultZ);
	void fromAxises(vec3 xaxis, vec3 yaxis, vec3 zaxis);

	float& operator [](int index);

private:

};

#endif // !QUATERNION_H
