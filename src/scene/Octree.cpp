#include "Octree.h"
#include<algorithm>
#include<iostream>
Octree::Octree()
{
	isfind = false;
}

Octree::~Octree()
{
}

void Octree::init(AABB aabb,int k)
{
	root = new NodeData(aabb);
	root->parent = NULL;
	maxDepth = 5;
	this->k = k;
	initChild(root, 1);
}

void Octree::initChild(NodeData * root, int d)
{
	if (d > maxDepth)
	{
		return;
	}
	auto childAABB = root->aabb.division(d,k);
	for (int i = 0; i < 8; ++i)
	{
		root->Children[i] = new NodeData(childAABB[i]);
		root->Children[i]->parent = root;
		initChild(root->Children[i], d+1);
	}
}

bool Octree::add(DrawNode3D * node)
{
	return add(root, node);
}

void Octree::cutByCamera( Camera * camera)
{
	cutByCamera(root, camera);
}

void Octree::updateNode(DrawNode3D * node)
{
	check(node);
}

void Octree::setDepth(int d)
{
	maxDepth = d;
}

void Octree::check(DrawNode3D * node)
{
	auto p = root;

	if (!check(root, node, p))
	{
		if (!this->add(p, node))
		{
			for (int i = 0; i < 8; ++i)
			{
				if (add(p->parent->Children[i], node))
				{
					return;
				}
			}
		}
	}
	isfind = false;
}

bool Octree::add(NodeData * root, DrawNode3D * node)
{
	if (root->aabb.contains(node->getAABB()))
	{
		if (root->Children[0] ==NULL)
		{
			root->list.push_back(node);
		}
		else
		{
			for (int i = 0; i < 8; ++i)
			{
				if (add(root->Children[i], node))
				{
					return true;
				}
				root->list.push_back(node);
			}
		}
		return true;
	}
	return false;
}

void Octree::cutByCamera(NodeData * root, Camera * camera)
{
	if (camera->isOutFrustum(root->aabb))
	{
		setUnDraw(root);
	}
	else
	{
		if (!root->Children[0])
			return;
		for (int i = 0; i < 8; ++i)
		{
			cutByCamera(root->Children[i], camera);
		}
	}

}

void Octree::setUnDraw(NodeData * root)
{
	if (!root)
		return;

	for (int i = 0; i < root->list.size(); ++i)
	{
		root->list[i]->setDrawable(false);
	}

	if (root->Children[0] == NULL)
		return;

	for (int i = 0; i < 8; ++i)
	{
		setUnDraw(root->Children[i]);
	}
}

bool Octree::check(NodeData * root, DrawNode3D * node,NodeData *p)
{
	for (int i = 0; i < root->list.size(); ++i)
	{
		if (root->list[i] == node)
		{
			auto res = std::find(root->list.begin(), root->list.end(), node);
			root->list.erase(res);
			p = root->parent;
			isfind = true;
			if (root->aabb.contains(node->getAABB()))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	if (!root->Children[0])
		return false;
	
	for (int i = 0; i < 8; ++i)
	{
		if (check(root->Children[i], node, p))
		{
			return true;
		}
		else
		{
			if (isfind)
				return false;
		}
	}
	return false;
}

NodeData::NodeData()
{
	for (int i = 0; i < 8; ++i)
	{
		Children[i] = NULL;
	}
}

NodeData::NodeData(AABB aabb) :aabb(aabb)
{
	for (int i = 0; i < 8; ++i)
	{
		Children[i] = NULL;
	}
}
