#include "MoveBy.h"

MoveBy::MoveBy()
{
}

MoveBy::~MoveBy()
{
}

MoveBy * MoveBy::create(float duration, vec3 frompos, vec3 distance)
{
	auto moveby = new MoveBy();
	moveby->setDuration(duration);
	moveby->setStart(frompos);
	moveby->setDistance(distance);
	return nullptr;
}

void MoveBy::doAction(Node * node, float dt)
{
	float d = dt / (1.0 / getCurTime());
	vec3 move = start + distance * d;
	node->setPosition(move);
}

void MoveBy::finish(Node * node)
{
	vec3 end = start + distance;
	node->setPosition(end);
}

void MoveBy::setDistance(vec3 d)
{
	distance = d;
}

void MoveBy::setStart(vec3 p)
{
	start = p;
}

vec3 MoveBy::getStart()
{
	return start;
}
