#include "boss.h"
#include"EventManager.h"

Boss* Boss::instance = nullptr;
Boss::Boss()
{
	window = new GLFW_Window();
}

Boss * Boss::share()
{
	if (!instance)
	{
		instance = new Boss();
	}
	return instance;
}

void Boss::draw()
{
	SceneManager::share()->draw();
}

GLFW_Window * Boss::getWin() const
{
	return window;
}

void Boss::update(float delta)
{
	deltaTime = delta;
	EventManager::share()->use();
	SceneManager::share()->check();
	SceneManager::share()->draw();



	Render::share()->renderAll();
}

float Boss::getFPS()
{
	return 1.0 / deltaTime;
}


vec2 Boss::getWinSize() const
{
	return getWin()->getSize();
}

float Boss::getWinWidth() const
{
	return getWin()->getWidth();
}

float Boss::getWinHeight() const
{
	return getWin()->getHeight();
}

float Boss::getDeltatime()
{
	return deltaTime;
}

SceneManager * Boss::getSceneMrg()
{
	return SceneManager::share();
}
