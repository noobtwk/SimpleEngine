#pragma once
#ifndef NODE_H
#define NODE_H
#include"vec2.h"
#include"vec3.h"
#include"mat4.h"
#include<vector>
#include"Action.h"
#include"ActionManager.h"

class Action;

class Node
{
public:
	Node();
	virtual ~Node();

	static Node * create();
	void setPosition(const vec3 &v);
	void setPosition(float x, float y, float z);
	void setPosition(float x, float y);
	vec3 getPosition();
	void addChild(Node *node);
	void setScale(const vec3 &v);
	vec3 getScale() const;

	void setRotateE(const vec3 &r);
	void setRotateE(float x, float y, float z);
	vec3 getRotateE();
	void setRotateQ(Quaternion &q);
	Quaternion getRotateQ() const;
	vec3 getWorldPos();
	Node *getParent();
	void setTag(unsigned int tag);
	void setName(std::string n);
	std::string getName() const;
	unsigned int getTag() const;
	void setLocalPriority(unsigned int p);
	unsigned int getLocalPriority() const;
	void setGlobalPriority(unsigned int p);
	unsigned int getGlobalPriority() const;
	Node *getChildByTag(unsigned int tag);
	Node *getChildByName(std::string n);
	Node *getChildByIndex(int i);

	void check();

	void runAction(Action * a);

	ActionManager * getActionMrg();


	mat4 getTransform() ;
	mat4 getModel() ;
	mat4 getTranslate() ;
	mat4 getRotateM() ;
	mat4 getScaleM() ;

	void cacheTransform();

	void recache();

	void hide();
	void appear();

	void visitDraw();
	void deleteChild(Node *node);

	bool getIsAlive();
	bool getIsDrawable();
	int getChildAmount();

	bool getIsNeedToUpdate();
	bool getParentIsNeedToUpdate();
	void setIsNeedToUpdate(bool i);

	static bool sortchild(Node *a,Node *b);
	void sortChildren();

	virtual void update(float dt);
	virtual void draw();

protected:
	bool isAlive;
	bool isDrawable;
	std::vector<Node *> children;
	Quaternion rotate;
	vec3 Euler;
	vec3 scale;
	vec3 position;
	Node *parent;
	unsigned int Tag;
	unsigned int Localpriority;
	unsigned int Globalpriority;
	std::string name;
	mat4 worldTransformMartix;
	ActionManager *actionMrg;
	
	bool isNeedToUpdate;

};


#endif // !NODE_H
