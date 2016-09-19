#pragma once
#ifndef FONT_H
#define FONT_H

#include<ft2build.h>
#include FT_FREETYPE_H  
#include<string>
#include"GlyphAtlas.h"
#include"GlyphData.h"

class Font
{
public:
	Font(std::string filePath,unsigned int size);
	~Font();

	FT_Face * getFace() const;
	void setFace(FT_Face *fc);
	GlyphData getGlyphDataFromChar(unsigned long c);
	GlyphAtlas * getGlyphAtlas() const;
	unsigned int getCharIndex(unsigned long c);

private:
	void initASCLLmap();
	FT_Face *face;
	unsigned int size;
	GlyphAtlas *glyphAtlas;
	
};

#endif // !FONT_H
