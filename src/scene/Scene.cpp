#include "Scene.h"
#include"boss.h"

Scene::Scene()
{
	initCamera();
}

Scene * Scene::create()
{
	auto scene = new Scene();
	
	return scene;
}

void Scene::addChild(Node * node)
{
	root.addChild(node);
}

Node* Scene::getRoot() 
{
	return &root;
}

void Scene::setRoot(Node node)
{
	root = node;
}

void Scene::addCamera(Camera *c)
{
	camera3DList.push_back(c);
}

void Scene::initCamera()
{
	camera2D = Camera::createOrtho(0, Boss::share()->getWinWidth(), Boss::share()->getWinHeight(), 0, -1, 100);
	camera3D = Camera::createPerspective(60, 1.0f * Boss::share()->getWinWidth() / Boss::share()->getWinHeight(), 0.1, 100);
	camera3DList.push_back(camera3D);
}

Camera * Scene::get2DCamera() const
{
	return camera2D;
}

Camera * Scene::get3DCamera() const
{
	return camera3D;
}

void Scene::draw()
{
	root.visitDraw();
}

void Scene::check()
{
	root.check();
}
