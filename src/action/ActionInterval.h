#pragma once
#ifndef ACTIONINTERVAL_H
#define ACTIONINTERVAL_H
#include"Action.h"
#include"Node.h"

class ActionInterval: public Action
{
public:
	ActionInterval();
	~ActionInterval();

	virtual void update(Node * node,float dt);
	virtual bool Done();
	virtual void finish(Node *node);
	virtual void doAction(Node *node, float dt);

	void setDuration(float time);
	float getDuration();
	void setCurTime(float time);
	float getCurTime();

private:
	float duration;
	float curTime;
	Node *node;
};


#endif // !ACTIONINTERVAL_H
