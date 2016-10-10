#include "TextureManager.h"

TextureManager *TextureManager::instance = nullptr;
TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

TextureManager * TextureManager::share()
{
	if (!instance)
	{
		instance = new TextureManager();
	}
	return instance;
}

Texture2D * TextureManager::getOrCreateTex2D(const char * path,bool ahp)
{
	std::string s = path;
	if (ahp)
	{
		s += "1";
	}
	else
		s += "0";

	if (tex2DList[s] == nullptr)
	{
		auto tex = new Texture2D(path, ahp);
		tex2DList[s] = tex;
		return tex;
	}
	else
		return tex2DList[s];
	
}

TextureCube * TextureManager::getOrCreateCube(const char * right, const char * left, const char * top, const char * bottom, const char * back, const char * front)
{
	std::string s(right);
	s += left;
	s += top;
	s += bottom;
	s += back;
	s += front;
	if (texCubeListh[s] == nullptr)
	{
		auto cube = TextureCube::createCube(right, left, top, bottom, back, front);
		texCubeListh[s] = cube;
		return cube;
	}
	else
		return texCubeListh[s];
	
}
