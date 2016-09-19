#pragma once
#ifndef DRAWNODE2D_H
#define DRAWNODE2D_H
#include"DrawNode.h"
class DrawNode2D : public DrawNode
{
public:
	DrawNode2D();

	void setContantSize(vec2 c);
	void setAnchorPoint(vec2 a);

	vec3 getPos();

	vec2 getContantSize() const;
	vec2 getAnchorPoint() const;

private:
	vec2 contanSize;
	vec2 anchorPoint;
};

#endif // !DRAWNODE2D_H
