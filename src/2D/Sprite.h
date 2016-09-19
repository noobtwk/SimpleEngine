#pragma once
#ifndef SPRITE_H
#define SPRITE_H
#include<glew.h>
#include <string>
#include"Mesh.h"
#include"DrawNode2D.h"


class Sprite :public DrawNode2D
{
public:
	Sprite() ;
	~Sprite();
	static Sprite* createWithTexture(Texture2D *texture);
	static Sprite* createWithPath(const char *path,bool ahp);
	static Sprite* createWithColor(const vec3 &color, vec2 contentsize);

	void initWithTexture(Texture2D *tex);
	void initWithColor(const vec3 &color,vec2 contentsize);
	void initWithPath(const char *path, bool ahp);
	void setPos(const vec2 &v);
	void setPos(float x, float y);
	void initShader();
	
	void setRenderRect(vec2 size,vec2 lb = vec2(0.0f,0.0f),vec2 rt=vec2(1.0f,1.0f));

	virtual void draw();


	Mesh *getMesh();

private:
	Mesh *mesh;
};


#endif // !SPRITE_H
