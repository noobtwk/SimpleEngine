#include "RotateBy.h"

RotateBy::RotateBy()
{
}

RotateBy::~RotateBy()
{
}

RotateBy * RotateBy::create(float duration,vec3 start, vec3 angle)
{
	auto rotate = new RotateBy();
	rotate->setDuration(duration);
	rotate->setStart(start);
	rotate->setAngle(angle);
	return rotate;
}

void RotateBy::doAction(Node * node, float dt)
{
	float d = getCurTime() * (1.0 / getDuration());
	node->setRotateE(start + angle * d);
}

void RotateBy::finish(Node * node)
{
	node->setRotateE(start + angle);
}

void RotateBy::setStart(vec3 s)
{
	start = s;
}

void RotateBy::setAngle(vec3 a)
{
	angle = a;
}

