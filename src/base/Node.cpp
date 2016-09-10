#include "Node.h"

Node::Node() :isVaild(true), position(vec3()), parent(nullptr)
{
}

Node::~Node()
{
}

Node * Node::create()
{
	Node *node = new Node();
	return node;
}

void Node::setPosition(const vec3 & v)
{
	this->position = v;
}

vec3 Node::getPosition() const
{
	return position;
}

void Node::addChild(Node * node)
{
	children.push_back(node);
}

void Node::setScale(const vec3 &v)
{
	this->scale = v;
}

vec3 Node::getWoldPos()
{
	return position;
}

Node * Node::getParent()
{
	return this->parent;
}

void Node::setTag(unsigned int tag)
{
	this->Tag = tag;
}

void Node::setName(std::string n)
{
	name = n;
}

std::string Node::getName() const
{
	return name;
}

unsigned int Node::getTag() const
{
	return Tag;
}

void Node::setPriority(unsigned int p)
{
	priority = p;
}

unsigned int Node::getPriority() const
{
	return priority;
}

Node * Node::getChildByTag(unsigned int tag)
{
	for (auto c : children)
	{
		if (c->getTag() == tag)
			return c;
	}
	return nullptr;
}

Node * Node::getChildByTag(std::string n)
{
	for (auto t : children)
	{
		if (t->getName() == n)
			return t;
	}
	return nullptr;
}

void Node::draw()
{

}
