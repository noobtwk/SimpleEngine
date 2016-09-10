#pragma once
#ifndef LABEL_H
#define LABEL_H
#include"Node.h"
#include<string>
#include"Font.h"
#include"FontMrg.h"
#include"Mesh.h"
#include"GlyphAtlas.h"
#include"Shader.h"
#include"ShaderManager.h"

class Label : public Node
{
public:
	Label();
	~Label(){};

	static Label * create(std::string text,Font *font);
	static Label * create(std::string text,std::string path,int size);
	void initWithhFont(Font *font);
	void initWithPath(std::string path,unsigned int size);

	virtual void draw();
	void setContainSize(vec2 size);
	void setStr(std::string s);
	std::string getStr() const;
	void initMesh();
	void setShader();
	GlyphAtlas *getAtlas() const;
	vec3 getColor() const;
	void setColor(const vec3 &col);

private:
	void initAtlas();
	Font *font;
	vec2 containSize;
	std::string str;
	Mesh *mesh;
	GlyphAtlas *atlas;
	Shader *shader;
	vec3 color;
};

#endif // !LABEL_H
