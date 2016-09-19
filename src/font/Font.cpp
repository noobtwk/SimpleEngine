#include "Font.h"
#include"FontBackEnd.h"

Font::Font(std::string filePath, unsigned int size)
{
	face = new FT_Face();
	FontBackEnd::share()->initFont(this, filePath, size);
	this->size = size;
}

Font::~Font()
{
}

FT_Face * Font::getFace() const
{
	return face;
}

void Font::setFace(FT_Face *fc)
{
	face = fc;
}

GlyphData Font::getGlyphDataFromChar(unsigned long c)
{
	if (FT_Load_Char(*face, c, FT_LOAD_RENDER| FT_LOAD_DEFAULT))
	{
		std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
	};
	GlyphData t;
	t.initFromFace(face, c);
	return t;
	
}

GlyphAtlas * Font::getGlyphAtlas() const
{
	return glyphAtlas;
}

unsigned int Font::getCharIndex(unsigned long c)
{
	return FT_Get_Char_Index(*face,c);
}

void Font::initASCLLmap()
{
	glyphAtlas = new GlyphAtlas();
	for (int i = 0; i < 128; ++i)
	{
		glyphAtlas->addGlyphData(getGlyphDataFromChar(i));
	}
	glyphAtlas->generate();
	glyphAtlas->generateTex();
}
