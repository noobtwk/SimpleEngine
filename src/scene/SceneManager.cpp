#include "SceneManager.h"

SceneManager * SceneManager::instance = nullptr;
SceneManager::SceneManager():curScene(nullptr),preScene(nullptr)
{
}

SceneManager * SceneManager::share()
{
	if (!instance)
	{
		instance = new SceneManager();
	}
	return instance;
}

void SceneManager::addScene(Scene * scene)
{
	sceneList.push_back(scene);
}

void SceneManager::setCurScene(Scene * scene)
{
	curScene = scene;
}


Scene * SceneManager::getCurScene() const
{
	return curScene;
}

Scene * SceneManager::getPreScene() const
{
	return preScene;
}


void SceneManager::draw()
{
	curScene->draw();
}

void SceneManager::check()
{
	curScene->check();
}

void SceneManager::replaceScene(Scene * scene)
{
	curScene = scene;
}
