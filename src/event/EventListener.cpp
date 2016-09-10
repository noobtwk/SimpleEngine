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
