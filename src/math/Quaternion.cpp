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

Quaternion Quaternion::slerp(Quaternion start, Quaternion end, float dt)
{
	Quaternion result;
	float cosHalfTheta = start[0] * end[0] + start[1] * end[1] + start[2] * end[2] + start[3] * end[3],
		halfTheta,
		sinHalfTheta,
		ratioA,
		ratioB;

	if (fabsf(cosHalfTheta) >= 1.0) {
		result = start;
		return result;
	}

	halfTheta = acosf(cosHalfTheta);
	sinHalfTheta = sqrtf(1.0f - cosHalfTheta * cosHalfTheta);

	if (fabsf(sinHalfTheta) < 0.001f) {
		result[0] = (start[0] * 0.5f + end[0] * 0.5f);
		result[1] = (start[1] * 0.5f + end[1] * 0.5f);
		result[2] = (start[2] * 0.5f + end[2] * 0.5f);
		result[3] = (start[3] * 0.5f + end[3] * 0.5f);
		return result;
	}

	ratioA = sinf((1 - dt) * halfTheta) / sinHalfTheta;
	ratioB = sinf(dt * halfTheta) / sinHalfTheta;

	result[0] = (start[0] * ratioA + end[0] * ratioB);
	result[1] = (start[1] * ratioA + end[1] * ratioB);
	result[2] = (start[2] * ratioA + end[2] * ratioB);
	result[3] = (start[3] * ratioA + end[3] * ratioB);
	return result;
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
	float halfRadx = MathUtil::radians(Euler.x / 2.0f);
	float halfRady = MathUtil::radians(Euler.y / 2.0f);
	float halfRadz = -MathUtil::radians(-Euler.z / 2.0f);

	float coshalfRadx = cosf(halfRadx), sinhalfRadx = sinf(halfRadx), coshalfRady = cosf(halfRady), sinhalfRady = sinf(halfRady), coshalfRadz = cosf(halfRadz), sinhalfRadz = sinf(halfRadz);
	x = sinhalfRadx * coshalfRady * coshalfRadz - coshalfRadx * sinhalfRady * sinhalfRadz;
	y = coshalfRadx * sinhalfRady * coshalfRadz + sinhalfRadx * coshalfRady * sinhalfRadz;
	z = coshalfRadx * coshalfRady * sinhalfRadz - sinhalfRadx * sinhalfRady * coshalfRadz;
	w = coshalfRadx * coshalfRady * coshalfRadz + sinhalfRadx * sinhalfRady * sinhalfRadz;
}

void Quaternion::QuaToEuler(float *resultX, float *resultY, float *resultZ)
{
	float _rotationX, _rotationY, _rotationZ;

	_rotationX = atan2f(2.f * (w * x + y * z), 1.f - 2.f * (x * x + y * y));
	float sy = 2.f * (w * y - z * x);
	sy = MathUtil::clamp(sy, -1, 1);
	_rotationY = asinf(sy);
	_rotationZ = atan2f(2.f * (w * z + x * y), 1.f - 2.f * (y * y + z * z));

	_rotationX = MathUtil::angles(_rotationX);
	_rotationY = MathUtil::angles(_rotationY);
	_rotationZ = -MathUtil::angles(_rotationZ);

	(*resultX) = _rotationX;
	(*resultY) = _rotationY;
	(*resultZ) = _rotationZ;
}

void Quaternion::fromAxises(vec3 xaxis, vec3 yaxis, vec3 zaxis)
{
	float trace = xaxis.x + yaxis.y + zaxis.z + 1.0f;

	if (trace > 0.01)
	{
		float s = 0.5f / sqrtf(trace);
		w = 0.25f / s;
		x = (yaxis.z - zaxis.y) * s;
		y = (zaxis.x - xaxis.z) * s;
		z = (xaxis.y - yaxis.x) * s;
	}
	else
	{
		if (xaxis.x > yaxis.y && xaxis.x > zaxis.z)
		{
			float s = 0.5f / sqrtf(1.0f + xaxis.x - yaxis.y - zaxis.z);
			w = (yaxis.z - zaxis.y) * s;
			x = 0.25f / s;
			y = (yaxis.x + xaxis.y) * s;
			z = (zaxis.x + xaxis.z) * s;
		}
		else if (yaxis.y > zaxis.z)
		{
			float s = 0.5f / sqrtf(1.0f + yaxis.y - xaxis.x - zaxis.z);
			w = (zaxis.x - xaxis.z) * s;
			x = (yaxis.x + xaxis.y) * s;
			y = 0.25f / s;
			z = (zaxis.y + yaxis.z) * s;
		}
		else
		{
			float s = 0.5f / sqrtf(1.0f + zaxis.z - xaxis.x - yaxis.y);
			w = (xaxis.y - yaxis.x) * s;
			x = (zaxis.x + xaxis.z) * s;
			y = (zaxis.y + yaxis.z) * s;
			z = 0.25f / s;
		}
	}
}

float & Quaternion::operator[](int index)
{
	switch (index)
	{
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	case 3:
		return w;
		break;
	default:
		break;
	}
}


