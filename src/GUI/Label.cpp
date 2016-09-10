#include "Label.h"
#include<glm.hpp>
#include<matrix_transform.hpp>
#include"RenderCommand.h"
#include"Render.h"
#include"Transform.h"

Label::Label():font(nullptr),str(""),mesh(nullptr), atlas(nullptr),shader(nullptr),color(vec3(1.0f,1.0f,1.0f))
{
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

void Label::initWithhFont(Font * font)
{
	this->font = font;
	setShader();
}

void Label::initWithPath(std::string path,unsigned int size)
{
	this->font = FontMrg::share()->getFont(path, size);
	setShader();
}

void Label::draw()
{
	RenderCommand c(mesh,shader,atlas->getTex(),getPosition(),getColor(),RenderCommand::GUI);
	c.setZorder(priority);
	Render::share()->addRenderCommand(c);
}

void Label::setContainSize(vec2 size)
{
	containSize = size;
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
		int diff = data->data.rows - data->data.top + (atlas->getmHeight() - data->data.rows);
		cmesh->addIndice(indices, 6);
		cmesh->addVertices(vertices, 4);
		mat4 trans;
		glm::mat4 t;
		if (diff != 0)
		{
			float r = oY = diff;
			trans.translate(vec3(oX + data->data.left, r, 0.0f));
			t = glm::translate(t, glm::vec3(oX + data->data.left, r, 0.0f));
		}
		mesh->merge(cmesh, trans);
		oX += data->data.advance;
		delete cmesh;
	}
}

void Label::setShader()
{
	shader = ShaderManager::share()->creatOrAdd("H:\\VS\\game\\shaders\\text.vs", "H:\\VS\\game\\shaders\\text.frag");
}

GlyphAtlas * Label::getAtlas() const
{
	return atlas;
}

vec3 Label::getColor() const
{
	return color;
}

void Label::setColor(const vec3 & col)
{
	color = col;
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
