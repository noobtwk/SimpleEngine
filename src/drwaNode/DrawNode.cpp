#include "DrawNode.h"

DrawNode::DrawNode() :camera(nullptr) , shader(nullptr),tex(nullptr) ,color(vec3(1,1,1))
{
}

Camera * DrawNode::getCamera() const
{
	return camera;
}

Shader * DrawNode::getShader() const
{
	return shader;
}

Texture2D * DrawNode::getTex() const
{
	return tex;
}

void DrawNode::setCamera(Camera * c)
{
	camera = c;
}

void DrawNode::setShader(Shader * s)
{
	shader = s;
}

void DrawNode::setTex(Texture2D * t)
{
	tex = t;
}

void DrawNode::setColor(vec3 c)
{
	color = c;
}

void DrawNode::setColor(float r, float b, float g)
{
	setColor(vec3(r, g, b));
}

vec3 DrawNode::getColor()
{
	return color;
}
