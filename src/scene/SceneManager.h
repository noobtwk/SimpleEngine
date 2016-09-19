#pragma once
#ifndef SCENEMANAGER_H
#define SCNENMANAGER_H
#include"Scene.h"
#include<vector>
class Scene;

class SceneManager
{
public:
	SceneManager();

	static SceneManager* share();

	void addScene(Scene * scene);

	void setCurScene(Scene * scene);

	Scene* getCurScene() const;
	Scene* getPreScene() const;
	void draw();
	void check();
	void replaceScene(Scene * scene);


private:
	static SceneManager* instance;
	std::vector<Scene*> sceneList;
	Scene* curScene;
	Scene* preScene;
};


#endif // !SCENEMANAGER_H
