#include "RenderCommand.h"

RenderCommand::RenderCommand(Mesh * mesh, Shader * shader,Camera* camera ,Texture2D *texture, vec3 pos, vec3 col, RenderType type)
	:mesh(mesh), shader(shader), tex(texture), type(type), Zorder(0), pos(pos), color(col),camera(camera)
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

vec3 RenderCommand::getPos() const
{
	return pos;
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
	return RenderType();
}

