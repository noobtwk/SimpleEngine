#pragma once
#ifndef RENDER_H
#define RENDER_H
#include"RenderCommand.h"
#include<vector>
#include<algorithm>
#include"mat4.h"
#include"FrameBuffer.h"

class RenderCommand;
class Render
{
public:
	Render();
	~Render() {};
	
	static Render *share();

	void addRenderCommand(RenderCommand rendercommand);

	void render(RenderCommand &rendercommand);
	void renderSkyBox();

	void renderAll();

	void renderAllSprite();

	void renderAll3DSprite();

	void renderAllGUI();

	void DefferRender();

	void Clear();
	
	void setEnable2DRender(bool isEnable2D);
	bool getEnable2DRender() const;

	void setEnableGUIRender(bool isEnableGUI) ;
	bool getEnableGUIRender() const;

	void setEnable3DRender(bool isEnable3D);
	bool getEnable3DRender() const;

	void passLightData(RenderCommand &rendercommand);

	static bool sortByDepth(RenderCommand a,RenderCommand b);

	void sort3DSprite();

	void enableDefferRender();
	void disalblerDefferRender();

	void initMesh();

private:
	std::vector<RenderCommand> Sprite2DCommand;
	std::vector<RenderCommand> GUICommand;
	std::vector < RenderCommand> Sprite3DCommand;
	bool enable2DRender;
	bool enableGUIRender;
	bool enable3DRender;
	Shader *deffer;
	Shader *defferLigth;
	bool defferRender;
	bool first;
	Mesh *quad;

	FrameBuffer *fbo;

	static Render *instance;
};

#endif // !RENDER_H
