#pragma once
#ifndef ROTATEBY_H
#define ROTATEBY_H
#include"ActionInterval.h"

class RotateBy : public ActionInterval
{
public:
	RotateBy();
	~RotateBy();

	static RotateBy * create(float duration, vec3 start, vec3 angle);
	virtual void doAction(Node * node, float dt);
	virtual void finish(Node * node);

	void setStart(vec3 s);
	void setAngle(vec3 a);
private:
	vec3 angle;
	vec3 start;
};


#endif // !ROTATEBY_H
