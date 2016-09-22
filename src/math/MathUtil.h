#ifndef MATHUTIL_H
#define MATHUTIL_H
class MathUtil
{
public:
	MathUtil();
	~MathUtil() {};

	static float PI;
	static float radians(float theta);
	static float angles(float rad);
	static unsigned int nextPow2(unsigned int num);
	static float clamp(float v, float low, float high);
private:

};


#endif // !MATHUTIL_H

