#pragma once
#ifndef SCALEBY_H
#define SCALEBY_H
#include"ActionInterval.h"


class ScaleBy : public ActionInterval
{
public:
	ScaleBy();
	~ScaleBy();

	static ScaleBy * create(float duration, vec3 startscale, vec3 scale);

	virtual void doAction(Node *node, float dt);
	virtual void finish(Node *node);
	
	void setStartScale(vec3 s);
	void setEndScale(vec3 s);

private:
	vec3 startScale;
	vec3 endScale;
};

#endif // !SCALEBY_H
