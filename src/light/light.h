#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include"vec3.h"
class Light
{
public:
	Light();
	Light(vec3 color, vec3 pos, float intensity);
	Light(vec3 color, vec3 pos);
	~Light();

	vec3 getColor();
	void setColor(vec3 col);

	void setIntensity(float i);
	float getIntensity();

	void setPosition(vec3 pos);
	vec3 getPosition();

private:
	vec3 color;
	vec3 position;
	float intensity;
};

#endif // !LIGHT_H
