#include "spot.h"
#include"MathUtil.h"
#include<algorithm>


Spot::Spot(vec3 pos, vec3 dir, float cut) :direction(dir),cutOff(cos(MathUtil::radians(cut))),outCutOff(cos(MathUtil::radians( cut + 5.0f)))
{
	setPosition(pos);

}

Spot::Spot(vec3 pos, vec3 dir, float cut, float outCut) :direction(dir),cutOff(cos(MathUtil::radians(cut))),outCutOff(cos(MathUtil::radians(outCut)))
{
	setPosition(pos);
}

Spot * Spot::creatSpot(vec3 pos, vec3 dir, float cut)
{
	auto light = new Spot(pos, dir, cut);
	return light;
}

Spot * Spot::creatSpot(vec3 pos, vec3 dir, float cut, float outCut)
{
	auto light = new Spot(pos, dir, cut, outCut);
	return light;
}

Spot::~Spot()
{
}

vec3 Spot::getDirection()
{
	return direction;
}

void Spot::setDirection(vec3 dir)
{
	direction = dir;
}

void Spot::setCutOff(float cut)
{
	cutOff = cut;
}

float Spot::getCutOff()
{
	return cutOff;
}

void Spot::setOutCutOff(float out)
{
	outCutOff = out;
}

float Spot::getOutCutOff()
{
	return outCutOff;
}
