#include "RenderCommand.h"

RenderCommand::RenderCommand(Mesh * mesh, Shader * shader,Camera* camera ,Texture2D *texture, mat4 model, vec3 col, RenderType type)
	:mesh(mesh), shader(shader), tex(texture), type(type), Zorder(0), model(model), color(col),camera(camera), needLighting(false)
{
}

RenderCommand::RenderCommand(Mesh * mesh, Shader * shader, Camera * camera, Texture2D * texture, mat4 model, vec3 col, float depth, RenderType type)
	:mesh(mesh), shader(shader), tex(texture), type(type), Zorder(0), model(model), color(col), camera(camera),depth(depth), needLighting(false)
{
}

RenderCommand::RenderCommand(Mesh * mesh, Shader * shader, Camera * camera, Texture2D * texture, mat4 model, vec3 col, float depth, bool needLighting, RenderType type)
	: mesh(mesh), shader(shader), tex(texture), type(type), Zorder(0), model(model), color(col), camera(camera), depth(depth),needLighting(needLighting)
{

}

void RenderCommand::render()
{
}

void RenderCommand::setZorder(unsigned int z)
{
	Zorder = z;
}

unsigned int RenderCommand::getZorder() const
{
	return Zorder;
}

mat4 RenderCommand::getTransform() const
{
	return model;
}

vec3 RenderCommand::getColor() const
{
	return color;
}

Camera * RenderCommand::getCamera() const
{
	return camera;
}


RenderCommand::RenderType RenderCommand::getType() const
{
	return type;
}

float RenderCommand::getDepth() const
{
	return depth;
}

