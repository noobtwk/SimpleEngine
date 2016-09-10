#include "vec3.h"
#include<algorithm>
#include<math.h>
vec3::vec3()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

vec3::vec3(const vec3 & v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

vec3::vec3(float nx, float ny, float nz)
{
	this->x = nx;
	this->y = ny;
	this->z = nz;
}

vec3::vec3(const vec2 & v, float a)
{
	x = v.x;
	y = v.y;
	z = a;
}

bool vec3::operator==(const vec3 & v) const 
{
	return this->x==v.x&&this->y==v.y&&this->z==v.z;
}

bool vec3::operator!=(const vec3 & v) const
{
	return this->x!=v.x || this->y !=v.y || this->z !=v.z;
}

vec3 & vec3::operator=(const vec3 & v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

vec3 vec3::operator-() const
{
	return vec3(-this->x, -this->y, -this->z);
}

vec3 vec3::operator+(const vec3 & v) const
{
	return vec3(this->x+v.x,this->y+v.y,this->z+v.z);
}

vec3 vec3::operator-(const vec3 & v) const
{ 
	return vec3(this->x - v.x, this->y - v.y, this->z - v.z);
}

vec3 vec3::operator*(float a) const
{
	return vec3(this->x * a,this->y *a,this->z * a);
}

vec3 vec3::operator/(float a) const
{
	float t = 1.0 / a;
	return vec3(this->x * t, this->y * t, this->z * t);
}

vec3 & vec3::operator+=(const vec3 & v)
{
	this->x + v.x;
	this->y + v.y;
	this->z + v.z;
	return *this;
}

vec3 & vec3::operator-=(const vec3 & v)
{
	this->x - v.x;
	this->y - v.y;
	this->z - v.z;
	return *this;
}

vec3 & vec3::operator+=(float a)
{
	this->x += a;
	this->y += a;
	this->z += a;
	return *this;

}

vec3 & vec3::operator-=(float a) 
{
	this->x -= a;
	this->y -= a;
	this->z -= a;
	return *this;
}

vec3 & vec3::operator*=(float a)
{
	this->x *= a;
	this->y *= a;
	this->z *= a;
	return *this;
}

vec3 & vec3::operator/=(float a)
{
	float t = 1.0 / a;
	this->x *= t;
	this->y *= t;
	this->z *= t;
	return *this;
}

void vec3::normalize()
{
	float temp = this->x *this->x + this->y * this->y + this->z *this->z;
	if (temp > 0.0f)
	{
		float t = 1.0 / sqrtf(temp);
		this->x *= temp;
		this->y *= temp;
		this->z *= temp;
	}
}

float vec3::distance(const vec3 & a, const vec3 & b)
{
	float nx = a.x - b.x;
	float ny = a.y - b.y;
	float nz = a.z - b.z;
	return sqrt(nx*nx + ny*ny + nz*nz);
}

float vec3::dot(const vec3 & a, const vec3 & b)
{

	return a.x*b.x + a.y*b.y + a.z*b.z;
}

vec3 vec3::cross(const vec3 &a, const vec3 &b)
{
	float nx = a.y*b.z - a.z*b.y;
	float ny = a.z*b.x - a.x*b.z;
	float nz = a.x*b.y - a.y*b.x;
	return vec3(nx,ny,nz);
}


