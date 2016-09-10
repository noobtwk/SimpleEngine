#include "Render.h"
#include"RenderBackEnd.h"
#include"RenderType.h"
#include<matrix_transform.hpp>
#include"MathUtil.h"

Render *Render::instance = nullptr;
Render::Render() :enable2DRender(true), enableGUIRender(true)
{
}
bool SortByZorder(const RenderCommand &a, const RenderCommand &b)
{
	return a.getZorder() < b.getZorder();
}

Render * Render::share()
{
	if (!instance)
	{
		instance = new Render();
	}
	return instance;
}

void Render::addRenderCommand(RenderCommand rendercommand)
{
	switch (rendercommand.type)
	{
	case RenderCommand::GUI:
		GUICommand.push_back(rendercommand);
		break;
	case RenderCommand::Sprite:
		SpriteCommand.push_back(rendercommand);
		break;
	default:
		break;
	}
}
void Render::render(RenderCommand & rendercommand)
{
	if (rendercommand.mesh->IfNeedToUpdate())
	{
		if (rendercommand.type == RenderCommand::RenderType::ThreeD)
			rendercommand.mesh->calNormal();
		rendercommand.mesh->initRenderData();
	}
	mat4 model;
	mat4 projection;
	model.translate(rendercommand.getPos());
	projection.ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0, 1.0);
	rendercommand.shader->Use();
	rendercommand.shader->setMatrix4("model", model, false);
	rendercommand.shader->setMatrix4("projection", projection, false);
	rendercommand.shader->setColor("Color", rendercommand.getColor(), false);
	RenderBackEnd::share()->passTex((GLuint)0, rendercommand.tex->TextureID, RenderType::TexType::Tex2D);
	glBindVertexArray(rendercommand.mesh->getVAO());
	glDrawElements(GL_TRIANGLES, rendercommand.mesh->getIndicesSize(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void Render::renderAll()
{
	if (enable2DRender)
	{
		renderAllSprite();
	}
	if (enableGUIRender)
	{
		renderAllGUI();
	}
	if (enable3DRender)
	{
		renderAll3DSprite();
	}
}
void Render::renderAllSprite()
{
	std::sort(SpriteCommand.begin(), SpriteCommand.end(), SortByZorder);
	for (int i = 0; i < SpriteCommand.size(); ++i)
	{
		render(SpriteCommand[i]);
	}
}

void Render::renderAll3DSprite()
{
}

void Render::renderAllGUI()
{
	std::sort(GUICommand.begin(), GUICommand.end(), SortByZorder);
	for (int i = 0; i < GUICommand.size(); ++i)
	{
		render(GUICommand[i]);
	}
}


void Render::Clear()
{
	SpriteCommand.clear();
	GUICommand.clear();
}

void Render::setEnable2DRender(bool isEnable2D)
{
	enable2DRender = isEnable2D;
}

bool Render::getEnable2DRender() const
{
	return enable2DRender;
}

void Render::setEnableGUIRender(bool isEnableGUI) 
{
	enableGUIRender = isEnableGUI;
}

bool Render::getEnableGUIRender() const
{
	return enableGUIRender;
}

void Render::setEnable3DRender(bool isEnable3D)
{
	enable3DRender = isEnable3D;
}

bool Render::getEnable3DRender() const
{
	return enable3DRender;
}
