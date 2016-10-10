#include "directional.h"

Directional::Directional() :direction(vec3())
{
}

Directional::Directional(vec3 dir) : direction(dir)
{
}

Directional * Directional::create(vec3 dir)
{
	auto light = new Directional(dir);
	return light;
}

Directional::~Directional()
{
}

void Directional::setDirection(vec3 dir)
{
	direction = dir;
}

vec3 Directional::getDirection() const
{
	return direction;
}
