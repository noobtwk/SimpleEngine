#pragma once
#ifndef MOVEBY_H
#define MOVEBY_H
#include"ActionInterval.h"
class MoveBy : public ActionInterval
{
public:
	MoveBy();
	~MoveBy();

	static MoveBy * create(float duration, vec3 frompos, vec3 distance);

	virtual void doAction(Node* node, float dt);
	virtual void finish(Node *node);
	void setDistance(vec3 d);
	void setStart(vec3 p);
	vec3 getStart();
	

private:
	vec3 distance;
	vec3 start;
};

#endif // !MOVEBY_H
