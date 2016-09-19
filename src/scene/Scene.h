#pragma once
#ifndef SCENE_H
#define SCENE_H
#include"Node.h"
#include"Camera.h"
#include<vector>
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

	void draw();
	void check();

private:
	Node root;
	Camera * camera2D;
	Camera * camera3D;
	std::vector<Camera*> camera3DList;
};


#endif // !SCENE_H
