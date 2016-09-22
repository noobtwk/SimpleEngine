#include "ScaleTo.h"

ScaleTo::ScaleTo()
{
}

ScaleTo::~ScaleTo()
{
}

ScaleTo * ScaleTo::create(float duration, vec3 startscale, vec3 endscale)
{
	auto scaleto = new ScaleTo();
	scaleto->setDuration(duration);
	scaleto->setStartScale(startscale);
	scaleto->setEndScale(endscale);
	return scaleto;
}

void ScaleTo::doAction(Node * node, float dt)
{
	float d = getCurTime() *(1.0 / getDuration());
	auto scale = startScale + (endScale - startScale) * d;
	node->setScale(scale);
}

void ScaleTo::finish(Node * node)
{
	node->setScale(endScale);
}

void ScaleTo::setStartScale(vec3 s)
{
	startScale = s;
}

void ScaleTo::setEndScale(vec3 s)
{
	endScale = s;
}
