#include "DrawNode2D.h"

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

vec3 DrawNode2D::getPos()
{
	vec3 p = getPosition();
	auto h = contanSize.y*(1-anchorPoint.y);
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
