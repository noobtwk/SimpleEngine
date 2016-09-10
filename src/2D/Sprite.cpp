#include "Sprite.h"
#include<glm.hpp>
#include <type_ptr.hpp>
#include<matrix_transform.hpp>
#include"Render.h"
#include"ShaderManager.h"

Sprite::Sprite(): shader(nullptr),texture(nullptr),mesh(nullptr),contentSize(0.0,0.0),anchorPoint(0.0,0.0),color(1.0,1.0,1.0)
{
}

Sprite::~Sprite()
{
}

Sprite *Sprite::createWithTexture(Texture2D * texture)
{
	auto sprite = new Sprite();
	
	sprite->initWithTexture(texture);
	return sprite;
}

Sprite * Sprite::createWithPath(const char * path,bool ahp)
{
	auto sprite = new Sprite();
	sprite->initWithPath(path,ahp);
	return sprite;
}

Sprite * Sprite::createWithColor(const vec3 & color,vec2 contentsize)
{
	auto sprite = new Sprite();
	sprite->initWithColor(color,contentsize);
	return sprite;
}

void Sprite::initWithTexture(Texture2D * tex)
{
	contentSize = tex->getSize();
	mesh = new Mesh();
	this->texture = tex;
	setShader();
	setRenderRect(contentSize);
}

void Sprite::initWithColor(const vec3 & color, vec2 contentsize)
{
	mesh = new Mesh();
	this->color = color;
	contentSize = contentsize;
	setShader();
	setRenderRect(contentSize);
}

void Sprite::initWithPath(const char * path,bool ahp)
{
	mesh = new Mesh();
	texture = new Texture2D(path, ahp);
	contentSize = texture->getSize();
	setShader();
	setRenderRect(contentSize);
}

void Sprite::setPos(const vec2 & v)
{
	vec3 t(v.x, v.y, 0.0f);
	this->setPosition(t);
}


void Sprite::setShader()
{
	shader = ShaderManager::share()->creatOrAdd("H:\\VS\\game\\shaders\\sprite.vs", "H:\\VS\\game\\shaders\\sprite.frag");
}

Texture2D * Sprite::getTexture() const
{
	return texture;
}

Shader * Sprite::getShader() const
{
	return shader;
}

void Sprite::setRenderRect(vec2  size, vec2  lb, vec2  rt)
{
	mesh->Clear();
	mesh->addIndex(0);
	mesh->addIndex(1);
	mesh->addIndex(2);
	mesh->addIndex(0);
	mesh->addIndex(2);
	mesh->addIndex(3);
	mesh->addVertex(VertexData(vec3(0.0f, 0.0f, 0.0f), vec2(lb.x, lb.y)));
	mesh->addVertex(VertexData(vec3(size.x, 0.0f, 0.0f), vec2(rt.x, lb.y)));
	mesh->addVertex(VertexData(vec3(size.x, size.y, 0.0f), vec2(rt.x, rt.y)));
	mesh->addVertex(VertexData(vec3(0.0f, size.y, 0.0f), vec2(lb.x, rt.y)));
}

void Sprite::draw()
{
	RenderCommand com(mesh, shader,texture,getPosition(),getColor(), RenderCommand::RenderType::Sprite);
	com.setZorder(priority);
	Render::share()->addRenderCommand(com);
}

void Sprite::setColor(const vec3 & c)
{
	color = c;
}

vec3 Sprite::getColor() const
{
	return color;
}

