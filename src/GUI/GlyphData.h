#pragma once
#ifndef GLYPHDATA_H
#define GLYPHDATA_H
#include<ft2build.h>
#include FT_FREETYPE_H

struct GlyphData
{
	unsigned int rows;
	unsigned int width;
	int left;
	int top;
	unsigned int advance;
	unsigned char * buffer;
	unsigned char * glbuffer;
	unsigned long mchar;
	unsigned int height_p;
	unsigned int width_p;

	void initFromFace(FT_Face *face,unsigned long c);
	unsigned int getSpecialAdance(unsigned long c, unsigned int ad);
	bool isInvisibleChar(unsigned long c);


};

#endif // !GLYPHDATA_H
