#include "ActionInterval.h"

ActionInterval::ActionInterval() :duration(1.0),curTime(0.0)
{
}

ActionInterval::~ActionInterval()
{
}

void ActionInterval::update(Node * node, float dt)
{
	if (curTime <= duration)
	{
		doAction(node, dt);
	}
	curTime += dt;
	if (curTime > duration)
	{
		finish(node);
	}
}

bool ActionInterval::Done()
{
	if(duration >= curTime)
		return false;
	return true;
}

void ActionInterval::finish(Node *node)
{
}

void ActionInterval::doAction(Node * node, float dt)
{
}

void ActionInterval::setDuration(float time)
{
	duration = time;
}

float ActionInterval::getDuration()
{
	return duration;
}

void ActionInterval::setCurTime(float time)
{
	curTime = time;
}

float ActionInterval::getCurTime()
{
	return curTime;
}
