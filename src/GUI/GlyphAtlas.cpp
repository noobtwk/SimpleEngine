#include "GlyphAtlas.h"
#include "MathUtil.h"
const int ROW = 10;

GlyphAtlas::GlyphAtlas()
{
}

GlyphAtlas::~GlyphAtlas()
{
}

void GlyphAtlas::addGlyphData(GlyphData data)
{
	datalist.push_back(data);
}

void GlyphAtlas::generate()
{
	mHeight = datalist.front().rows;
	mWidth = datalist.front().width;
	for (int i = 0; i < datalist.size(); ++i)
	{
		mHeight = std::max(mHeight, datalist[i].rows);
		mWidth = std::max(mWidth, datalist[i].width);
	}
	int size = datalist.size();
	height = std::ceil((1.0 / ROW)*size);
	auto buffersize = (mHeight*height) *(mWidth * ROW) *sizeof(unsigned char);
	buffer = static_cast<unsigned char *>(malloc(buffersize));
	memset(buffer, 0, buffersize);
	for (int i = 0; i < datalist.size(); ++i)
	{
		auto Data = datalist[i];
		auto Row = i / ROW;
		auto Col = i%ROW;
		auto offset = Col * mWidth + Row * ROW *(mHeight * mWidth);
		for (int y = 0; y < Data.rows; ++y)
		{
			for (int x = 0; x < Data.width; ++x)
			{
				buffer[offset + x + y* ROW * mWidth] = Data.buffer[x + y*Data.width];
			}
		}
		auto t = new GlyphAtlasData();
		t->parent = this;
		t->data = Data;
		t->x = Col * mWidth;
		t->y = Row * mHeight;
		glyphMap[Data.mchar] = t;
	}

}

void GlyphAtlas::generateTex()
{
	auto Width = ROW * mWidth;
	auto Height = height * mHeight;
	auto Height_p = MathUtil::nextPow2(Height);
	auto Width_p = MathUtil::nextPow2(Width);

	auto glbuffer = new unsigned char[Height_p * Width_p];
	for (int j = 0; j < Height_p; ++j)
	{
		for (int i = 0; i < Width_p; ++i)
		{
			glbuffer[(i + j*Width_p)] = (j >= Height || i >= Width) ? 0 : buffer[i + j * Width];
		}
	}
	texture =  new Texture2D(glbuffer,Width_p, Height_p);
	delete[] glbuffer;

}

Texture2D * GlyphAtlas::getTex() const
{
	return texture;
}

unsigned int GlyphAtlas::getHeight() const
{
	return height;
}

GlyphAtlasData * GlyphAtlas::getData(unsigned long c) 
{

	return glyphMap[c];
}

void GlyphAtlas::Clear()
{
	datalist.clear();
	glyphMap.clear();
	free(buffer);
}

unsigned int GlyphAtlas::getmHeight() const
{
	return mHeight;
}

GlyphAtlasData::GlyphAtlasData()
{
}

vec2 GlyphAtlasData::UV(float u, float v)
{
	return vec2(U(u),V(v));
}

float GlyphAtlasData::U(float u)
{
	vec2 size = parent->getTex()->getSize();
	int posX = x + data.width * u;
	return (1.0f/size.x)*posX;
}

float GlyphAtlasData::V(float v)
{
	vec2 size = parent->getTex()->getSize();
	int posY = y + data.rows*v;

	return (1.0f / size.y) * posY;
}
