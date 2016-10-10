#pragma once
#ifndef DRAWNODE3D_H
#define DRAWNODE3D_H
#include"DrawNode.h"
#include"AABB.h"

class DrawNode3D : public DrawNode
{
public:
	DrawNode3D();
	~DrawNode3D();

	float getDepth() const;

	mat4 getModel();

	void initDepth();


private:
	AABB localAABB;
	float depth;
};

#endif // !DRAWNODE3D_H
