#pragma once
#ifndef DRAWNODE_H
#define DRAWNODE_H
#include"Node.h"
#include"Camera.h"
#include"Shader.h"
#include"TextureManager.h"

class DrawNode:public Node
{
public:
	DrawNode();

	Camera * getCamera() const;
	Shader *getShader() const;
	Texture2D *getTex() const;

	void setCamera(Camera *c);
	void setShader(Shader* s);
	void setTex(Texture2D *t);

	void setColor(vec3 c);
	void setColor(float r, float b, float g);
	vec3 getColor();

private:
	Camera *camera;
	Shader *shader;
	Texture2D *tex;
	vec3 color;
};


#endif // !DRAWNODE_H
