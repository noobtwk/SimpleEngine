#include "ActionManager.h"

ActionManager * ActionManager::instance = nullptr;
ActionManager::ActionManager()
{
}

ActionManager::~ActionManager()
{
}

ActionManager * ActionManager::share()
{
	if (instance)
	{
		instance = new ActionManager();
	}
	return instance;
}

void ActionManager::addAction(Action * a)
{
	list.push_back(a);
}

void ActionManager::stopAction(Action * a)
{
	auto res = std::find(list.begin(), list.end(),a);
	if (res != list.end())
		list.erase(res);
	delete a;
}

void ActionManager::run(float dt)
{
	for (auto i = list.begin();i!=list.end();)
	{
		auto a = (*i);
		a->update(node, dt);
		if (a->Done())
		{
			list.erase(i);
			if (list.size() == 0)
			{
				break;
			}
			delete a;
		}
		else
			i++;
	}
}

void ActionManager::setNode(Node * n)
{
	node = n;
}
