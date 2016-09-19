#include "Button.h"
#include"EventManager.h"
#include"Render.h"
#include"SceneManager.h"

Button::Button() :isClicked(false)
{
	mesh = new Mesh();
	EventManager::share()->addNodeListener(this, this);
	setIsSwallow(true);
	setCamera(SceneManager::share()->getCurScene()->get2DCamera());
}

Button * Button::createWithLabel(Label * l)
{
	auto button = new Button();
	button->label = l;
	button->type = TEXT;
	button->setContantSize(l->getContantSize());
	button->initShader();
	button->setColor(l->getColor());
	return button;
}

Button * Button::createWithcolor(vec3 c, vec2 size)
{
	auto button = new Button();
	button->setColor(c);
	button->setContantSize(size);
	button->type = COLOR;
	button->initShader();
	button->initMesh();
	button->cusColor = c;
	return button;
}

Button * Button::createWithText(std::string text, std::string filepath, int size)
{
	auto button = new Button();
	auto l = Label::create(text, filepath, size);
	button->label = l;
	button->type = TEXT;
	button->setContantSize(l->getContantSize());
	button->initShader();
	return button;
}

Button * Button::createWithSprite(Sprite * unClick, Sprite * Click)
{
	auto button = new Button();
	button->unclick = unClick;
	button->click = Click;
	button->type = SPRITE;
	button->curSprite = unClick;
	button->setContantSize(unClick->getContantSize());
	button->initShader();
	return button;
}

bool Button::onMousePress(int button, vec2 pos)
{
	if (isInRect(pos))
	{
		switch (type)
		{
		case Button::TEXT:
			label->setColor(80.0 / 255, 80.0 / 255, 80.0 / 255);
			break;
		case Button::SPRITE:
			curSprite = click;
			break;
		case Button::COLOR:
			setColor(80.0 / 255, 80.0 / 255, 80.0 / 255);
			break;
		default:
			break;
		}
		isClicked = true;
	}
	return false;
}

bool Button::onMouseMove(vec2 pos)
{
	if (isClicked)
	{
		return true;
	}
	return false;
}

bool Button::onMouseRelease(int button, vec2 pos)
{
	if (isClicked)
	{
		isClicked = false;
		switch (type)
		{
		case Button::TEXT:
			label->setColor(getColor());
			break;
		case Button::SPRITE:
			curSprite = unclick;
			break;
		case Button::COLOR:
			setColor(cusColor);
			break;
		default:
			break;
		}
		//callBack(this);
	}
	return false;
}

void Button::setCallBack(const std::function<void(Button*)>& callback)
{
	callBack = callback;
}

bool Button::isInRect(vec2 point)
{
	auto size = getContantSize();
	auto position = getPos();
	
	if (position.x <= point.x && position.y <= position.y && (position.x + size.x) >= point.x && (position.y + size.y) >= point.y)
		return true;

	return false;
}

void Button::initShader()
{
	auto shader = ShaderManager::share()->creatOrAdd("H:\\VS\\game\\shaders\\sprite_color.vs", "H:\\VS\\game\\shaders\\sprite_color.frag");
	setShader(shader);
}

void Button::initMesh()
{
	auto size = getContantSize();
	mesh->addIndex(0);
	mesh->addIndex(1);
	mesh->addIndex(2);
	mesh->addIndex(0);
	mesh->addIndex(2);
	mesh->addIndex(3);
	mesh->addVertex(VertexData(vec3(0, 0, 0), vec2(0, 0)));
	mesh->addVertex(VertexData(vec3(size.x, 0, 0), vec2(0, 0)));
	mesh->addVertex(VertexData(vec3(size.x, size.y, 0), vec2(0, 0)));
	mesh->addVertex(VertexData(vec3(0, size.y, 0), vec2(0, 0)));
}

void Button::draw()
{	
	switch (type)
	{
	case Button::TEXT:
	{
		RenderCommand com(label->getMesh(), label->getShader(), label->getCamera(), label->getTex(), label->getPos(), label->getColor(), RenderCommand::GUI);
		Render::share()->addRenderCommand(com);
	}
	break;
	case Button::SPRITE:
	{
		RenderCommand com(curSprite->getMesh(), curSprite->getShader(), curSprite->getCamera(), curSprite->getTex(), curSprite->getPos(), curSprite->getColor(), RenderCommand::GUI);
		Render::share()->addRenderCommand(com);
	}
		break;
	case Button::COLOR:
	{
		RenderCommand com(mesh,getShader(),getCamera(),getTex(),getPos(),getColor(),RenderCommand::GUI);
		Render::share()->addRenderCommand(com);
	}
		break;
	default:
		break;
	}
}
