#include "light.h"

Light::Light() :color(vec3(1,1,1)),position(vec3()),intensity(1)
{
}

Light::Light(vec3 color, vec3 pos, float intensity) :color(color),position(pos),intensity(intensity)
{
}

Light::Light(vec3 color, vec3 pos) :color(color),position(pos),intensity(1)
{
}

Light::~Light()
{
}

vec3 Light::getColor()
{
	return color;
}

void Light::setColor(vec3 col)
{
	color = col;
}

void Light::setIntensity(float i)
{
	intensity = i;
}

float Light::getIntensity()
{
	return intensity;
}

void Light::setPosition(vec3 pos)
{
	position = pos;
}

vec3 Light::getPosition()
{
	return position;
}
