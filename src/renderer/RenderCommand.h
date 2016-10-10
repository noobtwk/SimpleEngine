#pragma once
#ifndef RENDERCOMMAND
#define RENDERCOMMAND
#include"Mesh.h"
#include"Shader.h"
#include"Render.h"
#include"Texture2D.h"
#include"Camera.h"
class RenderCommand
{
	friend class Render;
public:
	enum RenderType {
		GUI,
		Sprite2D,
		Sprite3D
	};
	RenderCommand(Mesh *mesh,Shader *shader,Camera *camera,Texture2D *texture,mat4 model,vec3 col,RenderType type);
	RenderCommand(Mesh *mesh, Shader *shader, Camera *camera, Texture2D *texture, mat4 model, vec3 col, float depth, RenderType type);
	RenderCommand(Mesh *mesh, Shader *shader, Camera *camera, Texture2D *texture, mat4 model, vec3 col, float depth,bool needLighting ,RenderType type);
	~RenderCommand() {};

	void render();

	void setZorder(unsigned int z);
	unsigned int getZorder() const;

	mat4 getTransform() const;
	vec3 getColor() const;
	Camera *getCamera() const;

	RenderType getType() const;

	float getDepth() const;

private:
	unsigned int Zorder;
	Shader *shader;
	Mesh *mesh;
	RenderType type;
	Texture2D *tex;
	mat4 model;
	vec3 color;
	Camera * camera;
	float depth;
	bool needLighting;
};


#endif // !RENDERCOMMAND
