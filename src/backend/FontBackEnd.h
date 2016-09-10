#pragma once
#ifndef FONTBACKEND_H
#define FONTBACKEND_H
#include<ft2build.h>
#include FT_FREETYPE_H
#include<iostream>
#include"Font.h"

class FontBackEnd
{
public:
	FontBackEnd();
	~FontBackEnd();
	static FontBackEnd * share();
	void initFont(Font *font, std::string filePath, unsigned int size);

private:
	static FontBackEnd *instance;
	FT_Library *ft;

};

#endif // !FONTBACKEND_H
