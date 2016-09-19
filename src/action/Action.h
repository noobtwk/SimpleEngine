#pragma once
#ifndef ACTION_H
#define ACTION_H

class Node;
class Action
{
public:
	Action();
	~Action();
	virtual void update(Node * node, float dt);
	virtual bool Done();
	virtual void finish(Node *node);
	virtual void doAction(Node * node, float dt);

private:

};

#endif // !ACTION_H
