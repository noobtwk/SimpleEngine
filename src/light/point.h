#pragma once
#ifndef POINT_H
#define POINT_H
#include"light.h"

class Point :public Light
{
public:
	Point();
	Point(vec3 pos);
	Point(vec3 pos, float linear, float quadratic);

	static Point * create(vec3 pos);
	static Point * create(vec3 pos, float linear, float quadratic);

	~Point();

	float getConstant() const;

	float getLinear() const;
	void setLinear(float l);

	float getQuadratic() const;
	void setQuadratic(float q);



private:
	float constant;
	float linear;
	float quadratic;
};

#endif // !POINT_H
