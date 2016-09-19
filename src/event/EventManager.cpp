#include "EventManager.h"
#include"SceneManager.h"
EventManager * EventManager::instance = nullptr;
EventManager::EventManager()
{
}

EventManager * EventManager::share()
{
	if (!instance)
	{
		instance = new EventManager();
	}
	return instance;
}

void EventManager::addListener(EventListener * l)
{
	eventList.push_back(l); 
	sortFixedListener();
}

void EventManager::addNodeListener(Node * node, EventListener * l)
{
	auto res = nodeListMap.find(node);
	if (res != nodeListMap.end())
		return;
	nodeListMap[node] = l;
	l->setLinkNode(node);
}

void EventManager::handleOnkeyPress(int keycode)
{
	info i;
	i.type = KEY_PRESS;
	i.keycode = keycode;
	eventDeque.push_back(i);
}

void EventManager::handleOnkeyRelease(int keycode)
{
	info i;
	i.keycode = keycode;
	i.type = KEY_RELEASE;
	eventDeque.push_back(i);
}

void EventManager::handleOnMousePress(int bottom, vec2 pos)
{
	info i;
	i.pos = pos;
	i.type = MOUSE_PRESS;
	i.button = bottom;
	eventDeque.push_back(i);
}

void EventManager::handleOnMouseMove(vec2 pos)
{
	info i;
	i.type = MOUSE_MOVE;
	i.pos = pos;
	eventDeque.push_back(i);
}

void EventManager::handleOnMouseRelease(int bottom, vec2 pos)
{
	info i;
	i.pos = pos;
	i.button = bottom;
	i.type = MOUSE_RELEASE;
	eventDeque.push_back(i);
}

void EventManager::handleOnScroll(int x, int y)
{
	info i;
	i.type = SCROLL;
	i.y = y;
	eventDeque.push_back(i);
}

void EventManager::handleOnCharInput(unsigned int c)
{
	info i;
	i.c = c;
	i.type = CHAR_INPUT;
	eventDeque.push_back(i);
}

void EventManager::use()
{
	sortNodeListener();
	while (!eventDeque.empty())
	{
		auto i = eventDeque.front();
		switch (i.type)
		{
		case KEY_PRESS:
			useKeyPress(i.keycode);
			break;
		case KEY_RELEASE:
			useKeyRelease(i.keycode);
			break;
		case MOUSE_PRESS:
			useMousePress(i.button, i.pos);
			break;
		case MOUSE_RELEASE:
			useMouseRelease(i.button, i.pos);
			break;
		case MOUSE_MOVE:
			useMouseMove(i.pos);
			break;
		case SCROLL:
			useScroll(i.y);
			break;
		case CHAR_INPUT:
			useCharInput(i.c);
			break;
		default:
			break;
		}
		eventDeque.pop_front();
	}
}

bool EventManager::sortByPiority(EventListener * a, EventListener * b)
{
	return a->getFixedPiority() >=b->getFixedPiority();
}

void EventManager::sortFixedListener()
{
	std::stable_sort(eventList.begin(), eventList.end(), sortByPiority);
}

bool EventManager::sortByNodePiority(EventListener * a, EventListener * b)
{
	auto na = a->getLinkNode();
	auto nb = b->getLinkNode();
	return na->getGlobalPriority()>nb->getGlobalPriority();
}

void EventManager::sortNodeListener()
{
	auto root = SceneManager::share()->getCurScene()->getRoot();
	nodeListener.clear();
	visit(root);
	std::stable_sort(nodeListener.begin(), nodeListener.end(), sortByNodePiority);
}

void EventManager::visit(Node * n)
{
	if (!n->getIsDrawable())
	{
		return;
	}
	if (nodeListMap.find(n) != nodeListMap.end())
	{
		nodeListener.push_front(nodeListMap[n]);
	}
	if (n->getChildAmount() != 0)
	{
		for (int i = 0; i < n->getChildAmount(); ++i)
		{
			auto node = n->getChildByIndex(i);
			visit(node);
		}
	}
}

void EventManager::useKeyPress(int keycode)
{
	for (auto i : eventList)
	{
		if (i->onkeyPress(keycode) && i->isSwallow()) break;
	}
	for (auto i : nodeListener)
	{
		if (i->onkeyPress(keycode) && i->isSwallow())break;
	}
}

void EventManager::useKeyRelease(int keycode)
{
	for (auto i : eventList)
	{
		if (i->onkeyRelease(keycode) && i->isSwallow()) break;
	}
	for (auto i : nodeListener)
	{
		if (i->onkeyRelease(keycode) && i->isSwallow()) break;
	}
}

void EventManager::useMousePress(int button, vec2 p)
{
	for (auto i : eventList)
	{
		if (i->onMousePress(button, p) && i->isSwallow()) break;
	}
	for (auto i : nodeListener)
	{
		if (i->onMousePress(button, p) && i->isSwallow()) break;
	}
}

void EventManager::useMouseRelease(int button, vec2 p)
{
	for (auto i : eventList)
	{
		if (i->onMouseRelease(button, p) && i->isSwallow()) break;
	}
	for (auto i : nodeListener)
	{
		if (i->onMouseRelease(button, p) && i->isSwallow()) break;
	}
}

void EventManager::useMouseMove(vec2 p)
{
	for (auto i : eventList)
	{
		if (i->onMouseMove(p) && i->isSwallow()) break;
	}
	for (auto i : nodeListener)
	{
		if (i->onMouseMove(p) && i->isSwallow()) break;
	}
}

void EventManager::useScroll(int y)
{
	for (auto i : eventList)
	{
		if (i->onScroll(0, y) && i->isSwallow()) break;
	}
	for (auto i : nodeListener)
	{
		if (i->onScroll(0, y) && i->isSwallow()) break;
	}
}

void EventManager::useCharInput(unsigned int c)
{
	for (auto i : eventList)
	{
		if (i->onCharInput(c) && i->isSwallow()) break;
	}
	for (auto i : nodeListener)
	{
		if (i->onCharInput(c) && i->isSwallow()) break;
	}
}
