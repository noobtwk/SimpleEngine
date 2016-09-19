#pragma once
#ifndef GLYPHATLAS_H
#define GLYPHATLAS_H
#include<vector>
#include"GlyphData.h"
#include<map>
#include"Texture2D.h"
#include<algorithm>
class GlyphAtlas;
struct GlyphAtlasData
{
	GlyphAtlasData();
	GlyphData data;
	int x, y;
	GlyphAtlas *parent;
	vec2 UV(float u, float v);
	float U(float u);
	float V(float v);
};

class GlyphAtlas
{
public:
	GlyphAtlas();
	~GlyphAtlas();
	void addGlyphData(GlyphData data);
	void generate();
	void generateTex();
	Texture2D * getTex() const;
	unsigned int getHeight() const;
	GlyphAtlasData *getData(unsigned long c);
	void Clear();
	unsigned int getmHeight() const;

	

private:
	std::vector<GlyphData> datalist;
	unsigned char * buffer;
	std::map<unsigned long, GlyphAtlasData*> glyphMap;
	Texture2D *texture;
	unsigned int mHeight;
	unsigned int mWidth;
	unsigned int height;
};

#endif // !GLYPHATLAS_H
