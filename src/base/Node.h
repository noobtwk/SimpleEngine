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
class Scene;

class Node
{
public:
	enum Type
	{
		s2d,
		s3d
	};
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

	void setScene(Scene *s);

	void setType(Type t);

	void check();

	void runAction(Action * a);

	ActionManager * getActionMrg();


	mat4 getTransform() ;
	mat4 getModel() ;
	mat4 getTranslate() ;
	mat4 getRotateM() ;
	mat4 getScaleM() ;

	void cacheTransform();

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

	void setDrawable(bool i);
	void setIsAlive(bool i);

	virtual void update(float dt);
	virtual void draw();
	virtual void recache();

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
	Type type;
	
	Scene *scene;

	bool isNeedToUpdate;

};


#endif // !NODE_H
