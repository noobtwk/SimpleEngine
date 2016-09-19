#pragma once
#ifndef MOVETO_H
#define MOVETO_H
#include"ActionInterval.h"
#include"vec3.h"

class MoveTo : public ActionInterval
{
public:
	MoveTo();
	~MoveTo();

	static MoveTo * create(float duration, vec3 frompos, vec3 topos);

	virtual void doAction(Node* node, float dt);
	virtual void finish(Node *node);
	void setEnd(vec3 e);
	void setStart(vec3 p);
	vec3 getStart();

private:
	vec3 end;
	vec3 start;
};


#endif // !MOVETO_H
