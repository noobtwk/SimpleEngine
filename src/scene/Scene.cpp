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
	camera3D->initLookAt();
	camera3DList.push_back(camera3D);
	fpcam = FPCamera::create(camera3D);
	root.addChild(fpcam);
}

Camera * Scene::get2DCamera() const
{
	return camera2D;
}

Camera * Scene::get3DCamera() const
{
	return camera3D;
}

FPCamera * Scene::getFPCamera()
{
	return fpcam;
}

void Scene::addPointLight(Point *l)
{
	pointLight.push_back(l);
}

void Scene::addSpotLight(Spot * l)
{
	spotLight.push_back(l);
}

void Scene::setAmbient(Ambient  a)
{
	ambientLight = a;
}

void Scene::setDirLight(Directional * d)
{
	dirLight = d;
}

Ambient Scene::getAmbient()
{
	return ambientLight;
}

bool Scene::haveDirLight()
{
	if(dirLight==nullptr)
		return false;
	return true;
}

Directional* Scene::getDirLight()
{
	return dirLight;
}

bool Scene::havePointLight()
{
	return pointLight.size()!=0;
}

bool Scene::haveSpotLight()
{
	return spotLight.size()!=0;
}

std::vector<Point*> Scene::getPointLight()
{
	return pointLight;
}

size_t Scene::getPointLightSize() const
{
	return pointLight.size();
}

std::vector<Spot*> Scene::getSpotLight()
{
	return spotLight;
}

size_t Scene::getSpotLightSize() const
{
	return spotLight.size();
}

void Scene::setSkyBox(SkyBox * s)
{
	skybox = s;
}

SkyBox * Scene::getSkyBox()
{
	return skybox;
}

void Scene::draw()
{
	root.visitDraw();
}

void Scene::check()
{
	root.check();
}
