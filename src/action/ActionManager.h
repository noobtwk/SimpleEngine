#pragma once
#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H
#include"Action.h"
#include<vector>
class Node;
class Action;
class ActionManager
{
public:
	ActionManager();
	~ActionManager();

	static ActionManager * share();
	void addAction(Action * a);

	void stopAction(Action * a);
	void run(float dt);

	void setNode(Node * n);

private:
	static ActionManager *instance;
	std::vector<Action*> list;
	Node *node;

};


#endif // !ACTIONMANAGER_H
