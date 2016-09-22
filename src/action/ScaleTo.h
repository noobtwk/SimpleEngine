#pragma once
#ifndef SCALETO_H
#define SCALETO_H
#include"ActionInterval.h"

class ScaleTo :public ActionInterval
{
public:
	ScaleTo();
	~ScaleTo();

	static ScaleTo * create(float duration,vec3 startscale,vec3 endscale);

	virtual void doAction(Node *node, float dt);
	virtual void finish(Node *node);

	void setStartScale(vec3 s);
	void setEndScale(vec3 s);

private:
	vec3 startScale;
	vec3 endScale;
};

#endif // !SCALE_H
