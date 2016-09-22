#include "RotateTo.h"

RotateTo::RotateTo()
{
}

RotateTo::~RotateTo()
{

}

RotateTo * RotateTo::create(float duration, vec3 start, vec3 end)
{
	auto rotateto = new RotateTo();
	rotateto->setDuration(duration);
	Quaternion s;
	s.EulerToQua(start);
	Quaternion e;
	e.EulerToQua(end);
	rotateto->setStart(s);
	rotateto->setEnd(e);
	return rotateto;
}

void RotateTo::doAction(Node * node, float dt)
{
	float d = getCurTime() * (1.0 / getDuration());
	Quaternion rotate= Quaternion::slerp(Start, End, d);
	node->setRotateQ(rotate);
}

void RotateTo::finish(Node * node)
{
	node->setRotateQ(End);
}

void RotateTo::setStart(Quaternion s)
{
	Start = s;
}

void RotateTo::setEnd(Quaternion e)
{
	End = e;
}
