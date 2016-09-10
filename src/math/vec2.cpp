#include "vec2.h"
#include<math.h>

vec2::vec2(const vec2 & v)
{
	this->x = v.x;
	this->y = v.y;
}

vec2::vec2(float nx, float ny):x(nx),y(ny)
{
}

vec2::vec2():x(0.0f),y(0.0f)
{
}

bool vec2::operator!=(const vec2 & v) const
{
	return this->x != v.x || this->y != v.y;
}

bool vec2::operator==(const vec2 & v) const
{
	return this->x==v.x&&this->y==v.y;
}

vec2 & vec2::operator=(const vec2 & v)
{
	this->x = v.x;
	this->y = v.y;
	return *this;
}

vec2 vec2::operator-() const
{
	return vec2(-this->x,-this->y);
}

vec2 vec2::operator+(const vec2 & v) const
{
	return vec2(this->x + v.x, this->y + v.y);
}

vec2 vec2::operator-(const vec2 & v) const
{
	return vec2(this->x - v.x, this->y - v.y);
}

vec2 vec2::operator+(float a) const
{
	return vec2(this->x + a, this -> y + a);
}

vec2 vec2::operator-(float a) const
{
	return vec2(this->x - a, this->y - a);
}

vec2 vec2::operator*(float a) const
{
	return vec2(this->x * a, this->y*a);
}

vec2 vec2::operator/(float a) const
{
	float t = 1.0 / a;
	return vec2(this->x *a, this->y * a);
}

vec2 & vec2::operator+=(const vec2 & v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

vec2 & vec2::operator-=(const vec2 & v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

vec2 & vec2::operator*=(float a)
{
	this->x *= a;
	this->y *= a;
	return *this;
}

vec2 & vec2::operator/=(float a)
{
	float t = 1.0 / a;
	this->x *= t;
	this->y *= t;
	return *this;
}



void vec2::normalize()
{
	float temp = this->x * this->x + this->y*this->y;
	if (temp > 0.0f)
	{
		float t = 1 / sqrtf(temp);
		this->x *= t;
		this->y *= t;
	}
}
