#include "Quaternion.h"
#include"MathUtil.h"
Quaternion::Quaternion():w(1.0f),x(0.0f),y(0.0f),z(0.0f)
{
}

Quaternion::Quaternion(float W, float X, float Y, float Z):w(W), x(X), y(Y),z(Z)
{
}

Quaternion & Quaternion::operator=(const Quaternion & q)
{
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
	return *this;
}

Quaternion Quaternion::operator-() const
{
	return Quaternion(-w, -x, -y, -z);
}

void Quaternion::normalize()
{
	float temp = x*x + y*y + z*z + w*w;
	if (temp > 0.0f)
	{
		float t = 1.0 / sqrtf(temp);
		w *= t;
		x *= t;
		y *= t;
		z *= t;
	}

}

Quaternion Quaternion::slerp(Quaternion q0, Quaternion q1, float t)
{
	Quaternion res;
	float cosOmega = q0.w*q1.w + q0.x*q1.x + q0.y*q1.y + q0.z*q1.z;
	if (cosOmega < 0.0f)
	{
		q1 = -q1;
		cosOmega = -cosOmega;
	}
	float k0, k1;
	if (cosOmega > 0.9999f)
	{
		k0 = 1.0f - t;
		k1 = t;
	}
	else
	{
		float sinOmega = sqrtf(1.0f - cosOmega*cosOmega);
		float omega = atan2(sinOmega, cosOmega);

		float oneOverSinOmega = 1.0 / sinOmega;

		k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
		k1 = sin(t*omega)* oneOverSinOmega;
	}
	res.w = q0.w*k0 + q1.w*k1;
	res.x = q0.x*k0 + q1.x*k1;
	res.y = q0.y*k0 + q1.y*k1;
	res.z = q0.z*k0 + q1.z*k1;
	return res;
}

void Quaternion::matrixToQua(vec3 Xaxis, vec3 Yaxis, vec3 Zaxis)
{
	Quaternion res;
	float nx, ny, nz, nw;
	float fourWSquaredMinusl = Xaxis.x + Yaxis.y + Zaxis.z;
	float fourXSquaredMinusl = Xaxis.x - Yaxis.y - Zaxis.z;
	float fourYSquaredMinusl = Yaxis.y - Xaxis.x - Zaxis.z;
	float fourZSquaredMinusl = Zaxis.z - Xaxis.x - Yaxis.y;

	int biggestIndex = 0;

	float fourBiggestSquaredMinusl = fourWSquaredMinusl;
	if (fourXSquaredMinusl > fourBiggestSquaredMinusl)
	{
		fourBiggestSquaredMinusl = fourXSquaredMinusl;
		biggestIndex = 1;
	}
	if (fourYSquaredMinusl > fourBiggestSquaredMinusl)
	{
		fourBiggestSquaredMinusl = fourYSquaredMinusl;
		biggestIndex = 2;
	}
	if (fourZSquaredMinusl > fourBiggestSquaredMinusl)
	{
		fourBiggestSquaredMinusl = fourZSquaredMinusl;
		biggestIndex = 3;
	}
	float biggestVal = sqrtf(fourBiggestSquaredMinusl + 1.0f) *0.5f;
	float mult = 0.25f / biggestVal;

	switch (biggestIndex)
	{
	case 0:
		nw = biggestVal;
		nx = (Yaxis.z - Zaxis.y) * mult;
		ny = (Zaxis.x - Xaxis.z) * mult;
		nz = (Xaxis.y - Yaxis.x) * mult;
		break;
	case 1:
		nw = biggestVal;
		nx = (Yaxis.z - Zaxis.y) * mult;
		ny = (Xaxis.y + Yaxis.x) * mult; 
		nz = (Zaxis.x + Xaxis.z) * mult;
		break;
	case 2:
		nw = biggestVal;
		nx = (Zaxis.x - Xaxis.z) * mult;
		ny = (Xaxis.y + Yaxis.x) * mult;
		nz = (Yaxis.z + Zaxis.y) * mult;
	case 3:
		nw = biggestVal;
		nx = (Xaxis.y - Yaxis.x) * mult;
		ny = (Zaxis.x + Xaxis.z) * mult;
		nz = (Yaxis.z + Zaxis.y) * mult;
	default:
		break;
	}
	w = nw;
	x = nx;
	y = ny;
	z = nz;

}

void Quaternion::EulerToQua(vec3 Euler)
{
	float RadX = MathUtil::radians(Euler.x / 2.0f);
	float RadY = MathUtil::radians(Euler.y / 2.0f);
	float RadZ = -MathUtil::radians(Euler.z / 2.0f);

	float cosRadX = cosf(RadX);
	float sinRadX = sinf(RadX);
	float cosRadY = cosf(RadY);
	float sinRadY = sinf(RadY);
	float cosRadZ = cosf(RadZ);
	float sinRadZ = sinf(RadZ);

	w = cosRadX * cosRadY * cosRadZ + sinRadX * sinRadY * sinRadZ;
	x = sinRadX * cosRadY * cosRadZ - cosRadX * sinRadY * sinRadZ;
	y = cosRadX * sinRadY * cosRadZ + sinRadX * cosRadY * sinRadZ;
	z = cosRadX * cosRadY * sinRadZ - sinRadX * sinRadY * cosRadZ;
}

void Quaternion::QuaToEuler(float * h, float * p, float * b)
{
	float rotatoX, rotatoY, rotatoZ;
	float sp = -2.0f * (y*z + w*x);
	if (fabs(sp) > 0.9999f)
	{
		rotatoX = 1.570796 * sp;
		rotatoY = atan2(-x*z - w*y, 0.5f - y*y - z*z);
		rotatoZ = 0.0f;
	}
	else
	{
		rotatoX = asin(sp);
		rotatoY = atan2(w*z - w*y, 0.5f - x*x - y*y);
		rotatoZ = atan2(x*y - w*z, 0.5f - x*x - z*z);
	}
	*h = rotatoX;
	*p = rotatoY;
	*b = rotatoZ;
}


