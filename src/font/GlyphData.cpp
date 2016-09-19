#include "GlyphData.h"
#include"MathUtil.h"

void GlyphData::initFromFace(FT_Face * face, unsigned long c)
{
	rows = (*face)->glyph->bitmap.rows;
	width = (*face)->glyph->bitmap.width;
	left = (*face)->glyph->bitmap_left;
	top = (*face)->glyph->bitmap_top;
	mchar = c;
	buffer = static_cast<unsigned char *>(malloc(width*rows*sizeof(char)));
	memcpy(buffer, (*face)->glyph->bitmap.buffer, width*rows);
	if (!isInvisibleChar(c))
	{
		advance = static_cast<int>((*face)->glyph->advance.x >> 6);
	}
	else
	{
		advance = getSpecialAdance(c, static_cast<int>((*face)->glyph->advance.x >> 6));
	}
	height_p = MathUtil::nextPow2(rows);
	width_p = MathUtil::nextPow2(width);

	glbuffer = new unsigned char[2 * height_p*width_p];
	for (int i = 0; i < height_p; ++i)
	{
		for (int j = 0; j < width_p; ++j)
		{
			glbuffer[2 * (j + i*width_p)] = glbuffer[2 * (j + i*width_p) + 1] =
				(j >= width_p || i >= height_p) ? 0 : buffer[i + j*width];
		}
	}

}

unsigned int GlyphData::getSpecialAdance(unsigned long c, unsigned int ad)
{
	switch (c)
	{
	case '\n':
		return 0;
		break;
	case '\t':
		return 4 * ad;
		break;
	default:
		break;
	}
	return 0;
}

bool GlyphData::isInvisibleChar(unsigned long c)
{
	if (c < 32)
	{
		return true;
	}
	return false;
}
