#include "mat4.h"
#include<string.h>

mat4::mat4()
{
	idenity();
}

void mat4::idenity()
{
	memset(val, 0, sizeof(val));
	val[0] = 1;
	val[5] = 1;
	val[10] = 1;
	val[15] = 1;
}

void mat4::rotate(const Quaternion & Q)
{
	float x = Q.x;
	float y = Q.y;
	float z = Q.z;
	float w = Q.w;
	
	float x2 = x + x;
	float y2 = y + y;
	float z2 = z + z;

	float xx = x2 * x;
	float yy = y2 * y;
	float zz = z2 * z;

	float xy = x2*y;
	float wz = w*z2;
	float xz = x2*z;
	float wy = w*y2;
	float yz = y2*z;
	float wx = w*x2;

	val[0] = 1 - yy - zz;
	val[1] = xy + wz;
	val[2] = xz - wy;
	val[3] = 0;

	val[4] = xy - wz;
	val[5] = 1 - xx - zz;
	val[6] = yz + wx;
	val[7] = 0;

	val[8] = xz + wy;
	val[9] = yz - wx;
	val[10] = 1 - xx - yy;
	val[11] = 0;

	val[12] = 0;
	val[13] = 0;
	val[14] = 0;
	val[15] = 1;
}

void mat4::rotate(float angle, vec3 axis)
{
	Quaternion q(cos(angle / 2), sin(angle / 2)*axis.x, sin(angle/2)*axis.y,sin(angle/2)*axis.z);
	rotate(q);
}

void mat4::translate(const vec3 & v)
{
	val[12] = v.x;
	val[13] = v.y;
	val[14] = v.z;
}

void mat4::scale(const vec3 & v)
{
	val[0] = v.x;
	val[5] = v.y;
	val[10] = v.z;
}

void mat4::perspective(float fovy, float aspect, float near, float far)
{
	float top = near * float(tan(fovy * 3.14159265358979323846 / 360.0));
	float right = top *aspect;
	frustum(-right, right, -top, top, near, far);
}

void mat4::ortho(float left, float right, float bottom, float top, float near, float far)
{
	float rl = right - left;
	float tb = top - bottom;
	float fn = far - near;
	val[0] = 2 / rl;
	val[1] = 0;
	val[2] = 0;
	val[3] = 0;
	val[4] = 0;
	val[5] = 2 / tb;
	val[6] = 0;
	val[7] = 0;
	val[8] = 0;
	val[9] = 0;
	val[10] = -2 / fn;
	val[11] = 0;
	val[12] = -(left + right) / rl;
	val[13] = -(top + bottom) / tb;
	val[14] = -(far + near) / fn;
	val[15] = 1;
}

void mat4::frustum(float left, float right, float bottom, float top, float near, float far)
{
	float rl = right - left;
	float tb = top - bottom;
	float fn = far - near;

	val[0] = (near * 2) / rl;
	val[1] = 0;
	val[2] = 0;
	val[3] = 0;
	val[4] = 0;
	val[5] = (near * 2) / tb;
	val[6] = 0;
	val[7] = 0;
	val[8] = (right + left) / rl;
	val[9] = (top + bottom) / tb;
	val[10] = -(far + near) / fn;
	val[11] = -1;
	val[12] = 0;
	val[13] = 0;
	val[14] = -(far*near * 2) / fn;
	val[15] = 0;
}

mat4 mat4::transpose()
{
	mat4 res;
	res.val[0] = val[0];
	res.val[1] = val[4];
	res.val[2] = val[8];
	res.val[3] = val[12];
	res.val[4] = val[1];
	res.val[5] = val[5];
	res.val[6] = val[9];
	res.val[7] = val[13];
	res.val[8] = val[2];
	res.val[9] = val[6];
	res.val[10] = val[10];
	res.val[11] = val[14];
	res.val[12] = val[3];
	res.val[13] = val[7];
	res.val[14] = val[11];
	res.val[15] = val[15];
	return mat4();
}

mat4 mat4::inverse()
{
	mat4 res;
	float a00 = val[0], a01 = val[1], a02 = val[2], a03 = val[3],
		a10 = val[4], a11 = val[5], a12 = val[6], a13 = val[7],
		a20 = val[8], a21 = val[9], a22 = val[10], a23 = val[11],
		a30 = val[12], a31 = val[13], a32 = val[14], a33 = val[15],

		b00 = a00 * a11 - a01 * a10,
		b01 = a00 * a12 - a02 * a10,
		b02 = a00 * a13 - a03 * a10,
		b03 = a01 * a12 - a02 * a11,
		b04 = a01 * a13 - a03 * a11,
		b05 = a02 * a13 - a03 * a12,
		b06 = a20 * a31 - a21 * a30,
		b07 = a20 * a32 - a22 * a30,
		b08 = a20 * a33 - a23 * a30,
		b09 = a21 * a32 - a22 * a31,
		b10 = a21 * a33 - a23 * a31,
		b11 = a22 * a33 - a23 * a32,

		d = (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06),
		invDet;

	invDet = 1 / d;

	res.val[0] = (a11 * b11 - a12 * b10 + a13 * b09) * invDet;
	res.val[1] = (-a01 * b11 + a02 * b10 - a03 * b09) * invDet;
	res.val[2] = (a31 * b05 - a32 * b04 + a33 * b03) * invDet;
	res.val[3] = (-a21 * b05 + a22 * b04 - a23 * b03) * invDet;
	res.val[4] = (-a10 * b11 + a12 * b08 - a13 * b07) * invDet;
	res.val[5] = (a00 * b11 - a02 * b08 + a03 * b07) * invDet;
	res.val[6] = (-a30 * b05 + a32 * b02 - a33 * b01) * invDet;
	res.val[7] = (a20 * b05 - a22 * b02 + a23 * b01) * invDet;
	res.val[8] = (a10 * b10 - a11 * b08 + a13 * b06) * invDet;
	res.val[9] = (-a00 * b10 + a01 * b08 - a03 * b06) * invDet;
	res.val[10] = (a30 * b04 - a31 * b02 + a33 * b00) * invDet;
	res.val[11] = (-a20 * b04 + a21 * b02 - a23 * b00) * invDet;
	res.val[12] = (-a10 * b09 + a11 * b07 - a12 * b06) * invDet;
	res.val[13] = (a00 * b09 - a01 * b07 + a02 * b06) * invDet;
	res.val[14] = (-a30 * b03 + a31 * b01 - a32 * b00) * invDet;
	res.val[15] = (a20 * b03 - a21 * b01 + a22 * b00) * invDet;

	return res;
}

mat4 & mat4::operator=(const mat4 & n)
{
	for (int i = 0; i < 16; ++i)
	{
		val[i] = n.val[i];
	}
	return *this;
}

mat4 mat4::operator*(const mat4 & other) const
{
	mat4 dest;
    auto mat2 = other.val;
    // Cache the matrix values (makes for huge speed increases!)
    float a00 = val[0], a01 = val[1], a02 = val[2], a03 = val[3],
            a10 = val[4], a11 = val[5], a12 = val[6], a13 = val[7],
            a20 = val[8], a21 = val[9], a22 = val[10], a23 = val[11],
            a30 = val[12], a31 = val[13], a32 = val[14], a33 = val[15],

            b00 = mat2[0], b01 = mat2[1], b02 = mat2[2], b03 = mat2[3],
            b10 = mat2[4], b11 = mat2[5], b12 = mat2[6], b13 = mat2[7],
            b20 = mat2[8], b21 = mat2[9], b22 = mat2[10], b23 = mat2[11],
            b30 = mat2[12], b31 = mat2[13], b32 = mat2[14], b33 = mat2[15];

    dest.val[0] = b00 * a00 + b01 * a10 + b02 * a20 + b03 * a30;
    dest.val[1] = b00 * a01 + b01 * a11 + b02 * a21 + b03 * a31;
    dest.val[2] = b00 * a02 + b01 * a12 + b02 * a22 + b03 * a32;
    dest.val[3] = b00 * a03 + b01 * a13 + b02 * a23 + b03 * a33;
    dest.val[4] = b10 * a00 + b11 * a10 + b12 * a20 + b13 * a30;
    dest.val[5] = b10 * a01 + b11 * a11 + b12 * a21 + b13 * a31;
    dest.val[6] = b10 * a02 + b11 * a12 + b12 * a22 + b13 * a32;
    dest.val[7] = b10 * a03 + b11 * a13 + b12 * a23 + b13 * a33;
    dest.val[8] = b20 * a00 + b21 * a10 + b22 * a20 + b23 * a30;
    dest.val[9] = b20 * a01 + b21 * a11 + b22 * a21 + b23 * a31;
    dest.val[10] = b20 * a02 + b21 * a12 + b22 * a22 + b23 * a32;
    dest.val[11] = b20 * a03 + b21 * a13 + b22 * a23 + b23 * a33;
    dest.val[12] = b30 * a00 + b31 * a10 + b32 * a20 + b33 * a30;
    dest.val[13] = b30 * a01 + b31 * a11 + b32 * a21 + b33 * a31;
    dest.val[14] = b30 * a02 + b31 * a12 + b32 * a22 + b33 * a32;
    dest.val[15] = b30 * a03 + b31 * a13 + b32 * a23 + b33 * a33;
    return dest;
}


vec4 mat4::operator*(const vec4 & v) const
{
	vec4 res;

	res.x = v.x * val[0] + v.y *val[4] + v.z*val[8] + v.w * val[12];
	res.y = v.x * val[1] + v.y * val[5] + v.z * val[9] + v.w * val[13];
	res.z = v.x * val[2] + v.y * val[6] + v.z * val[10] + v.w * val[14];
	res.w = v.x * val[3] + v.y * val[7] + v.z * val[11] + v.w * val[15];

	return res;
}

float * mat4::data()
{
	return val;
}

mat4 mat4::rotate(mat4 mat, const Quaternion & q)
{
	mat4 rotato;
	rotato.rotate(q);
	mat = mat * rotato;
	return mat;
}

mat4 mat4::translate(mat4 mat, const vec3 & v)
{
	mat4 t;
	t.translate(v);
	mat = mat * t;
	return mat;
}

mat4 mat4::scale(mat4 mat, const vec3 & v)
{
	mat4 s;
	s.scale(v);
	mat = mat * s;
	return mat;
}
