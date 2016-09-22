#include "ScaleBy.h"

ScaleBy::ScaleBy()
{
}

ScaleBy::~ScaleBy()
{
}

ScaleBy * ScaleBy::create(float duration, vec3 startscale, vec3 scale)
{
	auto scaleby = new ScaleBy();
	scaleby->setDuration(duration);
	scaleby->setStartScale(startscale);
	vec3 end = startscale;
	end.x = end.x * scale.x;
	end.y = end.y * scale.y;
	end.z = end.z * scale.z;
	scaleby->setEndScale(end);
	return scaleby;
}

void ScaleBy::doAction(Node * node, float dt)
{
	auto d = getCurTime() * (1.0 / getDuration());
	vec3 s = startScale + (endScale - startScale)*d;
	node->setScale(s);
}

void ScaleBy::finish(Node * node)
{
	node->setScale(endScale);
}

void ScaleBy::setStartScale(vec3 s)
{
	startScale = s;
}

void ScaleBy::setEndScale(vec3 s)
{
	endScale = s;
}
