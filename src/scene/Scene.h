#pragma once
#ifndef SCENE_H
#define SCENE_H
#include"Node.h"
#include"Camera.h"
#include<vector>
#include"FPCamera.h"
#include"ambient.h"
#include"spot.h"
#include"point.h"
#include"directional.h"
#include"SkyBox.h"
#include"Octree.h"

class Node;

class Scene
{
public:
	Scene();
	~Scene() {};

	static Scene * create();
	void addChild(Node *node);
	Node* getRoot() ;
	void setRoot(Node node);
	void addCamera(Camera *c);
	void initCamera();

	Camera *get2DCamera() const;
	Camera *get3DCamera() const;
	FPCamera * getFPCamera(); 

	void addPointLight(Point *l);
	void addSpotLight(Spot *l);
	void setAmbient(Ambient a);
	void setDirLight(Directional *d);

	Ambient getAmbient();

	bool haveDirLight();
	Directional* getDirLight();

	bool havePointLight();
	bool haveSpotLight();

	std::vector<Point*> getPointLight();
	size_t getPointLightSize() const;

	std::vector<Spot*> getSpotLight();
	size_t getSpotLightSize() const;

	void setSkyBox(SkyBox *s);
	SkyBox* getSkyBox();

	void enableOctree();
	void disableOctree();

	bool ifenableOctree();
	void updateOctreeNode(DrawNode3D *node);

	void draw();
	void check();

private:
	Node root;
	Camera * camera2D;
	Camera * camera3D;
	FPCamera * fpcam;
	std::vector<Camera*> camera3DList;
	Ambient ambientLight;
	Directional *dirLight;
	std::vector<Point*> pointLight;
	std::vector<Spot*> spotLight;
	SkyBox *skybox;
	Octree *octree;

	bool useOctree;

};


#endif // !SCENE_H