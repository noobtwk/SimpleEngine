#include "Label.h"
#include<glm.hpp>
#include<matrix_transform.hpp>
#include"RenderCommand.h"
#include"Render.h"
#include"Transform.h"
#include"SceneManager.h"

Label::Label():font(nullptr),str(""),mesh(nullptr), atlas(nullptr)
{
	setCamera(SceneManager::share()->getCurScene()->get2DCamera());
}

void Label::setPos(vec2 v)
{
	setPosition(vec3(v.x, v.y, 0.0));
}

void Label::setPos(float x, float y)
{
	setPos(vec2(x, y));
}

Label * Label::create(std::string text, Font * font)
{
	auto label = new Label();
	label->setStr(text);
	label->initWithhFont(font);

	return label;
}

Label * Label::create(std::string text, std::string path, int size)
{
	auto label = new Label();
	label->initWithPath(path, size);
	label->setStr(text);
	return label;
}

Label * Label::createL(std::string text, std::string path, int size)
{
	auto l = new Label();
	l->initWithPath(path, size);
	l->setStr(text);
	return l;
}

void Label::initWithhFont(Font * font)
{
	this->font = font;
	initShader();
}

void Label::initWithPath(std::string path,unsigned int size)
{
	this->font = FontMrg::share()->getFont(path, size);
	initShader();
}

void Label::draw()
{
	RenderCommand c(mesh,getShader(),getCamera(),atlas->getTex(),getPos(),getColor(),RenderCommand::GUI);
	c.setZorder(getGlobalPriority());
	Render::share()->addRenderCommand(c);
}


void Label::setStr(std::string s)
{
	str = s;
	initMesh();
}

std::string Label::getStr() const
{
	return str;
}

void Label::initMesh()
{
	initAtlas();
	if (!mesh)
	{
		mesh = new Mesh();
	}
	mesh->Clear();
	GLuint indices[]{
		0,1,2   ,0,2,3
	};
	int oX = 0, oY = 0;
	wstring wstr = Transform::stringToWstring(str);
	for (auto i : wstr)
	{
		auto cmesh = new Mesh();
		auto data = atlas->getData(i);
		
		float width = data->data.width;
		float height = data->data.rows;

		VertexData vertices[]{
			{ vec3(0.0f,0.0f,0.0f),data->UV(0.0f,0.0f) },
			{ vec3(width,0.0f,0.0f),data->UV(1.0f,0.0f) },
			{ vec3(width,height,0.0f),data->UV(1.0f,1.0f) },
			{ vec3(0.0f,height,0.0f),data->UV(0.0f,1.0f) }
		};
		int diff = data->data.rows - data->data.top + (atlas->getmHeight()- data->data.rows);
		cmesh->addIndice(indices, 6);
		cmesh->addVertices(vertices, 4);
		mat4 trans;
		if (diff != 0)
		{
			float r =  diff;
			trans.translate(vec3(oX + data->data.left, r, 0.0f));
		}
		mesh->merge(cmesh, trans);
		oX += data->data.advance;
		delete cmesh;
	}
	setContantSize(vec2(oX, atlas->getmHeight()));

}

void Label::initShader()
{
	auto shader = ShaderManager::share()->creatOrAdd("H:\\VS\\game\\shaders\\text.vs", "H:\\VS\\game\\shaders\\text.frag");
	setShader(shader);
}

GlyphAtlas * Label::getAtlas() const
{
	return atlas;
}

Mesh * Label::getMesh()
{
	return mesh;
}

void Label::initAtlas()
{
	if (!atlas)
	{
		atlas = new GlyphAtlas();
	}
	atlas->Clear();
	wstring wstr = Transform::stringToWstring(str);
	for (auto s : wstr)
	{
		atlas->addGlyphData(font->getGlyphDataFromChar(s));
	}
	atlas->generate();
	atlas->generateTex();
}
