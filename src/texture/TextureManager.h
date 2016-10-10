#pragma once
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include"Texture2D.h"
#include"TextureCube.h"
#include<unordered_map>
#include<string>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	static TextureManager* share();

	Texture2D * getOrCreateTex2D(const char* path, bool ahp);
	TextureCube *getOrCreateCube(const char* right, const char* left, const char* top, const char* bottom, const char* back, const char* front);

private:
	std::unordered_map<std::string, Texture2D*> tex2DList;
	std::unordered_map<std::string, TextureCube*> texCubeListh;
	static TextureManager* instance;
};

#endif // !TEXTUREMANAGER_H
