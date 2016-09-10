#pragma once
#ifndef NODE_H
#define NODE_H
#include"vec2.h"
#include"vec3.h"
#include"mat4.h"
#include<vector>

class Node
{
public:
	Node();
	virtual ~Node();

	static Node * create();
	void setPosition(const vec3 &v);
	vec3 getPosition() const;
	void addChild(Node *node);
	void setScale(const vec3 &v);
	vec3 getWoldPos();
	Node *getParent();
	void setTag(unsigned int tag);
	void setName(std::string n);
	std::string getName() const;
	unsigned int getTag() const;
	void setPriority(unsigned int p);
	unsigned int getPriority() const;
	Node *getChildByTag(unsigned int tag);
	Node *getChildByTag(std::string n);

	virtual void draw();
protected:
	bool isVaild;
	std::vector<Node *> children;
	vec3 scale;
	vec3 position;
	Node *parent;
	unsigned int Tag;
	unsigned int priority;
	std::string name;
};


#endif // !NODE_H
