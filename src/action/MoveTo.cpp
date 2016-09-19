#include "MoveTo.h"

MoveTo::MoveTo()
{
}

MoveTo::~MoveTo()
{
}

MoveTo * MoveTo::create(float duration,vec3 frompos, vec3 topos)
{
	auto moveto = new MoveTo();
	moveto->setDuration(duration);
	moveto->setEnd(topos);
	moveto->setStart(frompos);
	return moveto;
}

void MoveTo::doAction(Node * node, float dt)
{
	float d = getCurTime() * (1.0 /( getDuration()));
	vec3 move = start + (end - start) * d;
	node->setPosition(move);
	
}

void MoveTo::finish(Node *node)
{
	node->setPosition(end);
}

void MoveTo::setEnd(vec3 e)
{
	end = e;
}

void MoveTo::setStart(vec3 p)
{
	start = p;
}

vec3 MoveTo::getStart()
{
	return start;
}
