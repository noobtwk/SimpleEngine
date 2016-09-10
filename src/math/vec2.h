#ifndef VEC2_H
#define VEC2_H

class vec2
{
public:
	float x, y;
	vec2(const vec2 &v);
	vec2(float nx, float ny);
	vec2();

	bool operator !=(const vec2 &v) const;
	bool operator ==(const vec2 &v) const;
	vec2 &operator =(const vec2 &v);
	vec2 operator -() const;
	vec2 operator +(const vec2 &v) const;
	vec2 operator -(const vec2 &v) const;
	vec2 operator +(float a) const;
	vec2 operator -(float a) const;
	vec2 operator *(float a) const;
	vec2 operator /(float a) const;
	vec2 &operator +=(const vec2 &v);
	vec2 &operator -=(const vec2 &v);
	vec2 &operator *=(float a);
	vec2 &operator /=(float a);


	void normalize();

};

#endif // !VEC2_H
