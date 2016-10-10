#include "point.h"

Point::Point() :constant(1), linear(0.09), quadratic(0.032)
{
}

Point::Point(vec3 pos) :constant(1) ,linear(0.09),quadratic(0.032)
{
	setPosition(pos);
}

Point::Point(vec3 pos,float linear, float quadratic) : constant(1),linear(linear),quadratic(quadratic)
{
	setPosition(pos);
}

Point * Point::create(vec3 pos)
{
	auto light = new Point(pos);
	return light;
}

Point * Point::create(vec3 pos, float linear, float quadratic)
{
	auto light = new Point(pos, linear, quadratic);
	return light;
}

Point::~Point()
{
}

float Point::getConstant() const
{
	return constant;
}

float Point::getLinear() const
{
	return linear;
}

void Point::setLinear(float l)
{
	linear = l;
}

float Point::getQuadratic() const
{
	return quadratic;
}

void Point::setQuadratic(float q)
{
	quadratic = q;
}
