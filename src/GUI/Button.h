#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include"Label.h"
#include"DrawNode2D.h"
#include"EventListener.h"
#include"Sprite.h"
#include<functional>
#include"RenderCommand.h"

class Button :public DrawNode2D ,public EventListener
{
	enum Type
	{
		TEXT,
		SPRITE,
		COLOR
	};
public:
	Button();

	static Button * createWithLabel(Label *l);
	static Button * createWithcolor(vec3 c,vec2 size);
	static Button * createWithText(std::string text, std::string filepath, int size);
	static Button * createWithSprite(Sprite * unClick,Sprite *Click);

	virtual bool onMousePress(int button,vec2 pos);
	virtual bool onMouseMove(vec2 pos);
	virtual bool onMouseRelease(int button, vec2 pos);

	void setCallBack(const std::function<void(Button *)> &callback);

	bool isInRect(vec2 point);
	
	void initShader();

	void initMesh();

	virtual void draw();

private:
	Label *label;
	Sprite *unclick;
	Sprite *click;
	Type type;
	bool isClicked;
	vec3 cusColor;
	Mesh* mesh;

	std::function<void(Button*)> callBack;

	Sprite *curSprite;
};

#endif // !BUTTON_H
