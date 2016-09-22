#pragma once
#ifndef ROTATETO_H
#define ROTATETO_H
#include"ActionInterval.h"

class RotateTo : public ActionInterval
{
public:
	RotateTo();
	~RotateTo();

	static RotateTo * create(float duration, vec3 start, vec3 end);

	virtual void doAction(Node * node, float dt);
	virtual void finish(Node * node);

	void setStart(Quaternion s);
	void setEnd(Quaternion e);


private:
	Quaternion Start;
	Quaternion End;

};


#endif // !ROTATETO_
