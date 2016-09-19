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
	model.translate(rendercommand.getPos());

	auto a = rendercommand.getCamera()->getProjectionView()*model;

	rendercommand.shader->Use();
	rendercommand.shader->setMatrix4("mvp_Matrix", rendercommand.getCamera()->getProjectionView()*model,false);
	
	//rendercommand.shader->setMatrix4("projection", projecton1, false);
	//rendercommand.shader->setMatrix4("model", model, false);
	

	rendercommand.shader->setColor("Color", rendercommand.getColor(), false);
	if(rendercommand.tex)
		RenderBackEnd::share()->passTex((GLuint)0, rendercommand.tex->TextureID, RenderType::TexType::Tex2D);
	RenderBackEnd::share()->bindVAO(rendercommand.mesh->getVAO());
	RenderBackEnd::share()->drawElements(RenderType::DrawType::TRI, rendercommand.mesh->getIndicesSize(), 0);
	glDrawElements(GL_TRIANGLES, rendercommand.mesh->getIndicesSize(), GL_UNSIGNED_INT, 0);
	RenderBackEnd::share()->bindVAO(0);
}
void Render::renderAll()
{
	if (enableGUIRender)
	{
		renderAllGUI();
	}
	if (enable2DRender)
	{
		renderAllSprite();
	}
	if (enable3DRender)
	{
		renderAll3DSprite();
	}
	Clear();
}
void Render::renderAllSprite()
{
	std::stable_sort(SpriteCommand.begin(), SpriteCommand.end(), SortByZorder);
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
	std::stable_sort(GUICommand.begin(), GUICommand.end(), SortByZorder);
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
