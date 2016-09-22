#include "MathUtil.h"

float MathUtil::PI = 3.14159265f;
MathUtil::MathUtil()
{
}

float MathUtil::radians(float theta)
{

	return  PI* theta / 180.0f;
}

float MathUtil::angles(float rad)
{
	return rad * 180 / PI;
}

unsigned int MathUtil::nextPow2(unsigned int num)
{
	unsigned int tmp = 1;
	while (tmp<num)
	{
		tmp <<= 1;
	}
	return tmp;
}

float MathUtil::clamp(float v, float low, float high)
{
	if (v < low)
		return low;
	if (v > high)
		return high;
	return v;
}
