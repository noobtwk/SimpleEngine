#include "DrawNode2D.h"
#include<algorithm>
#include"MathUtil.h"

DrawNode2D::DrawNode2D() :contanSize(vec2(0, 0)), anchorPoint(vec2(0, 0))
{
}

void DrawNode2D::setContantSize(vec2 c)
{
	contanSize = c;
}

void DrawNode2D::setAnchorPoint(vec2 a)
{
	anchorPoint = a;
}

mat4 DrawNode2D::getModel()
{
	vec3 p = getPosition();
	auto h = contanSize.y*(1-anchorPoint.y);
	auto w = contanSize.x*(anchorPoint.x);
	p.x = p.x - w;
	p.y = p.y - h;
	vec3 s = getScale();
	h = (1 - s.y)*contanSize.y *(1-anchorPoint.y);
	w = (1 - s.x)*contanSize.x *anchorPoint.x;
	p.x = p.x + w;
	p.y = p.y + h;

	mat4 trans;
	trans.translate(p);
	trans = mat4::translate(trans, vec3(anchorPoint.x* contanSize.x,(1-anchorPoint.y)* contanSize.y,0));
	trans = mat4::rotate(trans, getRotateQ());
	trans = mat4::translate(trans, vec3(-anchorPoint.x* contanSize.x, -(1 - anchorPoint.y)*contanSize.y, 0));

	return trans * this->getScaleM() ;
}

vec3 DrawNode2D::getPos()
{
	vec3 p = getPosition();
	auto h = contanSize.y*(1 - anchorPoint.y);
	auto w = contanSize.x*(anchorPoint.x);
	p.x = p.x - w;
	p.y = p.y - h;
	return p;
}

vec2 DrawNode2D::getContantSize() const
{
	return contanSize;
}

vec2 DrawNode2D::getAnchorPoint() const
{
	return anchorPoint;
}
