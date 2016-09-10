#pragma once
#ifndef RENDERCOMMAND
#define RENDERCOMMAND
#include"Mesh.h"
#include"Shader.h"
#include"Render.h"
#include"Texture2D.h"
class RenderCommand
{
	friend class Render;
public:
	enum RenderType {
		GUI,
		Sprite,
		ThreeD
	};
	RenderCommand(Mesh *mesh,Shader *shader,Texture2D *texture,vec3 pos,vec3 col,RenderType type=Sprite);
	~RenderCommand() {};

	void render();

	void setZorder(unsigned int z);
	unsigned int getZorder() const;

	vec3 getPos() const;
	vec3 getColor() const;

	RenderType getType() const;

private:
	unsigned int Zorder;
	Shader *shader;
	Mesh *mesh;
	RenderType type;
	Texture2D *tex;
	vec3 pos;
	vec3 color;

};


#endif // !RENDERCOMMAND
