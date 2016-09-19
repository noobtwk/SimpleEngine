#include"EventListener.h"

EventListener::EventListener():fixedPiority(0),swallow(false)
{
}

EventListener::~EventListener()
{
}

bool EventListener::onkeyPress(int keycode)
{
	return false;
}

bool EventListener::onkeyRelease(int keycode)
{
	return false;
}

bool EventListener::onMousePress(int button, vec2 pos)
{
	return false;
}

bool EventListener::onMouseMove(vec2 pos)
{
	return false;
}

bool EventListener::onMouseRelease(int button, vec2 pos)
{
	return false;
}

bool EventListener::onScroll(int x, int y)
{
	return false;
}

bool EventListener::onCharInput(unsigned int c)
{
	return false;
}

int EventListener::getFixedPiority() const
{
	return fixedPiority;
}

void EventListener::setFiexdPiority(int piority)
{
	fixedPiority = piority;
}

void EventListener::setIsSwallow(bool isSwallow)
{
	swallow = isSwallow;
}

bool EventListener::isSwallow() const
{
	return swallow;
}

void EventListener::setLinkNode(Node * node)
{
	linkNode = node;
}

Node * EventListener::getLinkNode() const
{
	return linkNode;
}
