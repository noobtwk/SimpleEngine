#include "FontBackEnd.h"
#include "Font.h"

FontBackEnd * FontBackEnd::instance = nullptr;
FontBackEnd::FontBackEnd()
{
	ft = new FT_Library();
	if (FT_Init_FreeType(ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
}

FontBackEnd::~FontBackEnd()
{
}

FontBackEnd * FontBackEnd::share()
{
	if (!instance)
	{
		instance = new FontBackEnd();
	}
	return instance;
}

void FontBackEnd::initFont(Font *font, std::string filePath,unsigned int size)
{
	auto face = font->getFace();
	if (FT_New_Face(*ft, filePath.c_str(), 0, face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	FT_Set_Char_Size(*face, size << 6, 0, 96, 96);
	//FT_Set_Pixel_Sizes(*face, 0, size);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}
