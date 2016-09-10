#pragma once
#ifndef SPRITE_H
#define SPRITE_H
#include"Texture2D.h"
#include<glew.h>
#include <string>
#include"Shader.h"
#include"Node.h"
#include"Mesh.h"
#include"Camera.h"

class Sprite :public Node
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
	void setShader();
	Texture2D* getTexture() const;
	Shader *getShader() const;
	
	void setRenderRect(vec2 size,vec2 lb = vec2(0.0f,0.0f),vec2 rt=vec2(1.0f,1.0f));

	virtual void draw();

	void setColor(const vec3 &c);
	vec3 getColor() const;

private:
	Shader *shader;
	Texture2D *texture;
	vec2 anchorPoint;
	vec2 contentSize;
	vec3 color;
	Mesh *mesh;
	Camera *camera;
};


#endif // !SPRITE_H
