#pragma once
#ifndef OCTREE_H
#define OCTREE_H
#include"AABB.h"
#include"drawNode3D.h"
#include<vector>

struct NodeData {
	AABB aabb;
	std::vector<DrawNode3D *> list;
	NodeData *Children[8];
	NodeData *parent;
	NodeData();
	NodeData(AABB aabb);
};

class Octree
{
public:
	Octree();
	~Octree();

	void init(AABB aabb,int k);
	void initChild(NodeData *root,int d);	

	bool add(DrawNode3D *node);

	void cutByCamera( Camera *camera);

	void updateNode(DrawNode3D *node);

	void setDepth(int d);

	void check(DrawNode3D *node);

private:
	bool add(NodeData* root, DrawNode3D *node);
	void cutByCamera(NodeData *root, Camera *camera);
	void setUnDraw(NodeData *root);
	bool check(NodeData* root, DrawNode3D *node, NodeData *p);
	int maxDepth;
	NodeData *root;
	int k;
	bool isfind;
};


#endif // !OCTREE_H
