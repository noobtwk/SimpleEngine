#include "Sprite.h"
#include<glm.hpp>
#include <type_ptr.hpp>
#include<matrix_transform.hpp>
#include"Render.h"
#include"ShaderManager.h"
#include"SceneManager.h"

Sprite::Sprite(): mesh(nullptr)
{
	setCamera(SceneManager::share()->getCurScene()->get2DCamera());
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
	setContantSize( tex->getSize());
	mesh = new Mesh();
	setTex(tex);
	initShader();
	setRenderRect(getContantSize());
}

void Sprite::initWithColor(const vec3 & color, vec2 contentsize)
{
	mesh = new Mesh();
	setColor(color);
	setContantSize( contentsize);
	initShader();
	setRenderRect(getContantSize());
}

void Sprite::initWithPath(const char * path,bool ahp)
{
	mesh = new Mesh();
	auto texture = new Texture2D(path, ahp);
	setTex(texture);
	auto contentSize = texture->getSize();
	setContantSize(contentSize);
	initShader();
	setRenderRect(contentSize);
}

void Sprite::setPos(const vec2 & v)
{
	vec3 t(v.x, v.y, 0.0f);
	this->setPosition(t);
}

void Sprite::setPos(float x, float y)
{
	setPos(vec2(x, y));
}


void Sprite::initShader()
{
	if (getTex())
	{
		auto shader = ShaderManager::share()->creatOrAdd("H:\\VS\\game\\shaders\\sprite.vs", "H:\\VS\\game\\shaders\\sprite.frag"); 
		setShader(shader);
	}
	else
	{
		auto shader = ShaderManager::share()->creatOrAdd("H:\\VS\\game\\shaders\\sprite_color.vs", "H:\\VS\\game\\shaders\\sprite_color.frag");
		setShader(shader);
	}
	
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
	RenderCommand com(mesh, getShader(),getCamera(),getTex(),getPos(),getColor(), RenderCommand::RenderType::Sprite);
	com.setZorder(getGlobalPriority());
	Render::share()->addRenderCommand(com);
}



Mesh * Sprite::getMesh()
{
	return mesh;
}

