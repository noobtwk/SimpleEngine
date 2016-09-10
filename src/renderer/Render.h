#pragma once
#ifndef RENDER_H
#define RENDER_H
#include"RenderCommand.h"
#include<vector>
#include<algorithm>
#include"mat4.h"
class RenderCommand;
class Render
{
public:
	Render();
	~Render() {};
	
	static Render *share();

	void addRenderCommand(RenderCommand rendercommand);

	void render(RenderCommand &rendercommand);

	void renderAll();

	void renderAllSprite();

	void renderAll3DSprite();

	void renderAllGUI();

	void Clear();
	
	void setEnable2DRender(bool isEnable2D);
	bool getEnable2DRender() const;

	void setEnableGUIRender(bool isEnableGUI) ;
	bool getEnableGUIRender() const;

	void setEnable3DRender(bool isEnable3D);
	bool getEnable3DRender() const;


private:
	std::vector<RenderCommand> SpriteCommand;
	std::vector<RenderCommand> GUICommand;
	std::vector < RenderCommand> TDSpriteCommand;
	bool enable2DRender;
	bool enableGUIRender;
	bool enable3DRender;

	static Render *instance;
};

#endif // !RENDER_H
