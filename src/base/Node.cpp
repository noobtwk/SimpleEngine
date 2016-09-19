#include "Node.h"
#include<algorithm>
#include"boss.h"

Node::Node() :isAlive(true), position(vec3()), parent(nullptr), isDrawable(true),isNeedToUpdate(true),scale(vec3(1,1,1))
{
	Globalpriority = 0;
	Localpriority = 0;
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

void Node::setPosition(float x, float y, float z)
{
	setPosition(vec3(x, y, z));
}

void Node::setPosition(float x, float y)
{
	setPosition(vec3(x, y, 0));
}

vec3 Node::getPosition() 
{
	return position;
}

void Node::addChild(Node * node)
{
	children.push_back(node);
	if (node->getParent())
	{
		
	}
	else
	{
		node->parent = this;
		sortChildren();
	}
}

void Node::setScale(const vec3 &v)
{
	this->scale = v;
}

vec3 Node::getScale() const
{
	return scale;
}

void Node::setRotate(const vec3 & r)
{
	Euler = r;
	rotate.EulerToQua(Euler);
}

void Node::setRotate(float x, float y, float z)
{
	setRotate(vec3(x, y, z));
}

vec3 Node::getRotate() const
{
	return Euler;
}

vec3 Node::getWorldPos()
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

void Node::setLocalPriority(unsigned int p)
{
	Localpriority = p;
	if (parent)
	{
		parent->sortChildren();
	}
}

unsigned int Node::getLocalPriority() const
{
	return Localpriority;
}

void Node::setGlobalPriority(unsigned int p)
{
	Globalpriority = p;
	for (auto i : children)
	{
		if (i->getGlobalPriority() == 0)
		{
			i->setGlobalPriority(p);
		}
	}
}

unsigned int Node::getGlobalPriority() const
{
	return Globalpriority;
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

Node * Node::getChildByName(std::string n)
{
	for (auto t : children)
	{
		if (t->getName() == n)
			return t;
	}
	return nullptr;
}

Node * Node::getChildByIndex(int i)
{
	return children[i];
}

void Node::check()
{
	update(Boss::share()->getDeltatime());
	if(actionMrg)
		actionMrg->run(Boss::share()->getDeltatime());

	if (isNeedToUpdate)
	{
		recache();
	}
	for (auto i : children)
	{
		i->check();
	}
}

void Node::runAction(Action * a)
{
	if (!actionMrg)
	{
		actionMrg = new ActionManager();
		actionMrg->setNode(this);
	}
	actionMrg->addAction(a);
}

ActionManager * Node::getActionMrg()
{
	return actionMrg;
}


mat4 Node::getTransform() 
{
	if (isNeedToUpdate)
	{
		cacheTransform();
	}
	return worldTransformMartix;
}

mat4 Node::getModel()
{
	auto t = getTranslate();
	auto r = getRotateM();
	auto s = getScaleM();
	return getTranslate() * getRotateM() * getScaleM();
}

void Node::cacheTransform()
{
	auto p = this->getParent();
	if (p)
	{
		auto parentTrans = p->getTransform();
		worldTransformMartix = parentTrans * getModel();
	}
	else
	{
		auto a = getModel();
		worldTransformMartix = getModel();
	}
}

void Node::recache()
{
	cacheTransform();
}

void Node::hide()
{
	isDrawable = false;
}

void Node::appear()
{
	isDrawable = true;
}

void Node::visitDraw()
{
	if (isAlive && isDrawable)
	{
		draw();
	}
	for (int i = 0; i < children.size(); ++i)
	{
		children[i]->visitDraw();
	}

	if (!isAlive)
	{
		this->getParent()->deleteChild(this);
		delete this;

	}
}

void Node::deleteChild(Node * node)
{
	auto n = std::find(children.begin(), children.end(), node);
	if (n != children.end())
	{
		children.erase(n);
	}
}

bool Node::getIsAlive()
{
	return isAlive;
}

bool Node::getIsDrawable()
{
	return isDrawable;
}

int Node::getChildAmount()
{
	return children.size();
}

bool Node::getIsNeedToUpdate()
{
	return isNeedToUpdate;
}

void Node::setIsNeedToUpdate(bool i)
{
	isNeedToUpdate = i;
}

bool Node::sortchild(Node * a,Node *b)
{
	return a->getLocalPriority() < b->getLocalPriority();
}

void Node::sortChildren()
{
	std::stable_sort(children.begin(), children.end(), sortchild);
}




void Node::update(float dt)
{
}

void Node::draw()
{

}

mat4 Node::getTranslate() 
{
	mat4 trans;
	trans.translate(getPosition());
	return trans;
}

mat4 Node::getRotateM() 
{
	mat4 r;
	r.idenity();
	rotate.normalize();
	r.rotate(rotate);
	return r;
}

mat4 Node::getScaleM() 
{
	mat4 s;
	s.scale(scale);
	return s;
}


