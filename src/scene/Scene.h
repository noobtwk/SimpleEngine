#pragma once
#ifndef SCENE_H
#define SCENE_H
#include"Node.h"

class Scene
{
public:
	Scene();
	~Scene() {};

	static Scene * create();

	void visitDraw();


private:
	Node *root;


};


#endif // !SCENE_H
