#include "Render.h"
#include"RenderBackEnd.h"
#include"RenderType.h"
#include"MathUtil.h"
#include"SceneManager.h"
#include<iostream>
#include<string>
#include"boss.h"
#include"ShaderManager.h"
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <type_ptr.hpp>
Render *Render::instance = nullptr;
Render::Render() :enable2DRender(true), enableGUIRender(true), enable3DRender(true),defferRender(false),first(true)
{
	fbo = FrameBuffer::create(Boss::share()->getWinWidth(), Boss::share()->getWinHeight(), 3);
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
	case RenderCommand::Sprite2D:
		Sprite2DCommand.push_back(rendercommand);
		break;
	case RenderCommand::Sprite3D:
		Sprite3DCommand.push_back(rendercommand);
		break;
	default:
		break;
	}
}
void Render::render(RenderCommand & rendercommand)
{
	if(rendercommand.mesh->IfNeedToUpdate())
		rendercommand.mesh->initRenderData();

	Shader * shader;
	if (defferRender && rendercommand.getType()==RenderCommand::Sprite3D)
	{
		shader = deffer;
	}
	else
	{
		shader = rendercommand.shader;
	}

	shader->Use();
	shader->setMatrix4("mvp_Matrix",rendercommand.getCamera()->getProjectionView() * rendercommand.getTransform() ,false);
	shader->setMatrix4("model", rendercommand.getTransform(), false);
	
	if(!rendercommand.needLighting)
		shader->setColor("Color", rendercommand.getColor(), false);

	if(rendercommand.tex)
		RenderBackEnd::share()->passTex((GLuint)0, rendercommand.tex->TextureID, RenderType::TexType::Tex2D);

	RenderBackEnd::share()->bindVAO(rendercommand.mesh->getVAO());
	RenderBackEnd::share()->drawElements(RenderType::DrawType::TRI, rendercommand.mesh->getIndicesSize(), 0);
	RenderBackEnd::share()->bindVAO(0);
	
}
void Render::renderSkyBox()
{
	auto skybox = SceneManager::share()->getCurScene()->getSkyBox();
	if (skybox == nullptr)
	{
		return;
	}
	else
	{
		auto mesh = skybox->getMesh();
		if (mesh->IfNeedToUpdate())
			mesh->initRenderData();
		RenderBackEnd::share()->setDepthTestFuc(RenderType::DepthTestFuc::lessOrQua);
		auto shader = skybox->getShader();
		shader->Use();
		shader->setMatrix4("mvp_Matrix",skybox->getCamera()->getSkyBoxProjectionView() , false);
		
		RenderBackEnd::share()->passTex(0, skybox->getCube()->TextureID, RenderType::TexCube);
		RenderBackEnd::share()->bindVAO(mesh->getVAO());
		RenderBackEnd::share()->drawElements(RenderType::TRI, mesh->getIndicesSize(), 0);
		RenderBackEnd::share()->bindVAO(0);
		RenderBackEnd::share()->setDepthTestFuc(RenderType::DepthTestFuc::less);
	}
}
void Render::renderAll()
{
	if (enable3DRender)
	{
		if (defferRender)
		{
			if(!deffer)
				deffer = ShaderManager::share()->creatOrAdd("H:/VS/game/shaders/deffer.vs", "H:/VS/game/shaders/deffer.frag");
			if (!defferLigth)
				defferLigth = ShaderManager::share()->creatOrAdd("H:/VS/game/shaders/defferLight.vs", "H:/VS/game/shaders/defferLight.frag");
			DefferRender();
		}
		else
			renderAll3DSprite();
	}
	if (enable2DRender)
	{
		renderAllSprite();
	}
	if (enableGUIRender)
	{
		renderAllGUI();
	}
	renderSkyBox();
	Clear();
}
void Render::renderAllSprite()
{
	std::stable_sort(Sprite2DCommand.begin(), Sprite2DCommand.end(), SortByZorder);
	for (int i = 0; i < Sprite2DCommand.size(); ++i)
	{
		render(Sprite2DCommand[i]);
	}
}

void Render::renderAll3DSprite()
{
	sort3DSprite();
	RenderBackEnd::enableFuction(RenderType::Fuction::DepthTest);
	for (int i = 0; i < Sprite3DCommand.size(); ++i)
	{
		if(Sprite3DCommand[i].mesh->IfNeedToCal())
			Sprite3DCommand[i].mesh->calNormal();
		if(Sprite3DCommand[i].needLighting&&!defferRender)
			passLightData(Sprite3DCommand[i]);
		render(Sprite3DCommand[i]);
	}
}

void Render::renderAllGUI()
{
	std::stable_sort(GUICommand.begin(), GUICommand.end(), SortByZorder);
	for (int i = 0; i < GUICommand.size(); ++i)
	{
		render(GUICommand[i]);
	}
}

void Render::DefferRender()
{
	defferLigth->Use();
	defferLigth->setInt("gPosition", 0, false);
	defferLigth->setInt("gNormal", 1, false);
	defferLigth->setInt("gColor", 2, false);
	defferLigth->setInt("depthMap", 3, false);

	
	fbo->bindForWrite();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderAll3DSprite();

	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	if (!quad)
		initMesh();
	if (quad->IfNeedToUpdate())
		quad->initRenderData();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	defferLigth->Use();
	fbo->bindColorBuffer();
	fbo->bindDepthBuffer();

	RenderBackEnd::share()->bindVAO(quad->getVAO());
	RenderBackEnd::share()->drawElements(RenderType::DrawType::TRI, quad->getIndicesSize(), 0);
	RenderBackEnd::share()->bindVAO(0);
	
}


void Render::Clear()
{
	Sprite2DCommand.clear();
	GUICommand.clear();
	Sprite3DCommand.clear();
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

void Render::passLightData(RenderCommand &rendercommand)
{
	auto scene = SceneManager::share()->getCurScene();
	rendercommand.shader->Use();
	auto ambient = scene->getAmbient();
	rendercommand.shader->setVector3f("ambientL", ambient.getColor(), false);
	rendercommand.shader->setMatrix4("model", rendercommand.getTransform(), false);
	rendercommand.shader->setVector3f("viewPos", rendercommand.getCamera()->getPosition(), false);
	if (scene->haveDirLight())
	{
		auto dirLight = scene->getDirLight();
		rendercommand.shader->setInt("isDirLighting", 1, false);
		rendercommand.shader->setVector3f("dirLight.color", dirLight->getColor(), false);
		rendercommand.shader->setVector3f("dirLight.direction", dirLight->getDirection(), false);
	}
	else
	{
		rendercommand.shader->setInt("isDirLighting", 0, false);
	}
	if (scene->havePointLight())
	{
		auto size = scene->getPointLightSize();
		auto point = scene->getPointLight();
		rendercommand.shader->setInt("isPointLighting", 1, false);
		rendercommand.shader->setInt("pointSize", size, false);
		for (int i = 0; i < size; ++i)
		{

			char c[100];
			_itoa_s(i, c, 10);
			std::string s("pointLight[");
			s += c;
			s += "]";
			rendercommand.shader->setVector3f((s+".position").c_str(), point[i]->getPosition(), false);
			rendercommand.shader->setVector3f((s + ".color").c_str(), point[i]->getColor(), false);
			rendercommand.shader->setFloat((s + ".constant").c_str(), point[i]->getConstant(), false);
			rendercommand.shader->setFloat((s + ".linear").c_str(), point[i]->getLinear(), false);
			rendercommand.shader->setFloat((s + ".quadratic").c_str(), point[i]->getQuadratic(), false);
		}
	}
	else
	{
		rendercommand.shader->setInt("isPointLighting", 0, false);
	}
	if (scene->haveSpotLight())
	{
		auto size = scene->getSpotLightSize();
		auto spot = scene->getSpotLight();
		rendercommand.shader->setInt("isSpotLighting", 1, false);
		rendercommand.shader->setInt("spotSize", size, false);
		for (int i = 0; i < size; ++i)
		{
			char c[100];
			_itoa_s(i, c, 10);
			std::string s("spotLight[");
			s += c;
			s += "]";
			rendercommand.shader->setVector3f((s + ".position").c_str(), spot[i]->getPosition(), false);
			rendercommand.shader->setVector3f((s + ".direction").c_str(), spot[i]->getDirection(), false);
			rendercommand.shader->setVector3f((s + ".color").c_str(), spot[i]->getColor(), false);


			rendercommand.shader->setFloat((s + ".cutOff").c_str(), spot[i]->getCutOff(), false);
			rendercommand.shader->setFloat((s + ".outCutOff").c_str(), spot[i]->getOutCutOff(), false);

			rendercommand.shader->setFloat((s + ".constant").c_str(), spot[i]->getConstant(), false);
			rendercommand.shader->setFloat((s + ".linear").c_str(), spot[i]->getLinear(), false);
			rendercommand.shader->setFloat((s + ".quadratic").c_str(), spot[i]->getQuadratic(), false);
		}
	}
	else
	{
		rendercommand.shader->setInt("isSpotLighting", 0, false);
	}
}

bool Render::sortByDepth(RenderCommand  a, RenderCommand b)
{
	return a.getDepth() > b.getDepth();
}

void Render::sort3DSprite()
{
	std::stable_sort(Sprite3DCommand.begin(), Sprite3DCommand.end(), sortByDepth);
}

void Render::enableDefferRender()
{
	defferRender = true;
}

void Render::disalblerDefferRender()
{
	defferRender = false;
}

void Render::initMesh()
{
	quad = new Mesh();
	VertexData vertices[]
	{
		{vec3(-1,1,0),vec2(0,1)},
		{vec3(-1,-1,0),vec2(0,0)},
		{vec3(1,1,0),vec2(1,1)},
		{vec3(1,-1,0),vec2(1,0)}
	};
	GLuint indices[]
	{
		0,1,2, 1,3,2
	};
	quad->addVertices(vertices, sizeof(vertices) / sizeof(VertexData));
	quad->addIndice(indices, sizeof(indices) / sizeof(GLuint));
}