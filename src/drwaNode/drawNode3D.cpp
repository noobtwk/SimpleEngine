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

AABB DrawNode3D::getAABB()
{
	return worldAABB;
}

void DrawNode3D::setAABB(AABB aabb)
{
	localAABB = aabb;
}

mat4 DrawNode3D::getModel()
{

	return getTransform();
}

void DrawNode3D::initDepth()
{
	depth = vec3::distance(getCamera()->getPosition(), getPosition());
}

void DrawNode3D::recacheAABB()
{
	auto trans = getTransform();
	if (isNeedToUpdate)
	{
		worldAABB = localAABB;
		worldAABB.transform(trans);
	}
}

void DrawNode3D::recache()
{
	Node::recache();
	recacheAABB();
}
