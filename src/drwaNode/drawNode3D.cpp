#include "drawNode3D.h"

DrawNode3D::DrawNode3D()
{
}

DrawNode3D::~DrawNode3D()
{
}


float DrawNode3D::getDepth() const
{
	return depth;
}

mat4 DrawNode3D::getModel()
{

	return getTransform();
}

void DrawNode3D::initDepth()
{
	depth = vec3::distance(getCamera()->getPosition(), getPosition());
}
