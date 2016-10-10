#pragma once
#ifndef DIRECTIONAL_H
#define DIRECTIONAL_H
#include"light.h"

class Directional :public Light
{
public:
	Directional();
	Directional(vec3 dir);

	static Directional * create(vec3 dir);

	~Directional();

	void setDirection(vec3 dir);
	vec3 getDirection() const;

private:
	vec3 direction;
};

#endif // !DIRECTIONAL_H
