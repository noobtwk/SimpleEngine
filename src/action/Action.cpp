#include "Action.h"

Action::Action()
{
}

Action::~Action()
{
}

void Action::update(Node * node, float dt)
{
	doAction(node, dt);
}

bool Action::Done()
{
	return true;
}

void Action::finish(Node *node)
{
}

void Action::doAction(Node * node, float dt)
{

}
