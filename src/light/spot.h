#pragma once
#ifndef SPOT_H
#define SPOT_H
#include"point.h"

class Spot:public Point
{
public:
	Spot(vec3 pos, vec3 dir, float cut);
	Spot(vec3 pos, vec3 dir, float cut, float outCut);
	static Spot *creatSpot(vec3 pos, vec3 dir, float cut);
	static Spot *creatSpot(vec3 pos, vec3 dir, float cut, float outCut);

	~Spot();


	vec3 getDirection();
	void setDirection(vec3 dir);

	void setCutOff(float cut);
	float getCutOff();

	void setOutCutOff(float out);
	float getOutCutOff();

private:
	vec3 direction;
	float cutOff;
	float outCutOff;
};

#endif // !SPOT_H
