#pragma once
#ifndef LABEL_H
#define LABEL_H
#include"Node.h"
#include<string>
#include"Font.h"
#include"FontMrg.h"
#include"Mesh.h"
#include"GlyphAtlas.h"
#include"ShaderManager.h"
#include"DrawNode2D.h"

class Label : public DrawNode2D
{
public:
	Label();
	~Label(){};

	void setPos(vec2 v);
	void setPos(float x, float y);

	static Label * create(std::string text,Font *font);
	static Label * create(std::string text,std::string path,int size);
	static Label * createL(std::string text, std::string path, int size);
	void initWithhFont(Font *font);
	void initWithPath(std::string path,unsigned int size);

	virtual void draw();
	void setStr(std::string s);
	std::string getStr() const;
	void initMesh();
	void initShader();
	GlyphAtlas *getAtlas() const;


	Mesh *getMesh();

private:
	void initAtlas();
	Font *font;
	std::string str;
	Mesh *mesh;
	GlyphAtlas *atlas;
};

#endif // !LABEL_H
