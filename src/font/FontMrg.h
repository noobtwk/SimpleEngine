#pragma once
#ifndef FONTMRG_H
#define FONTMRG_H
#include"Font.h"
#include<string>
#include<vector>
#include<map>


class FontMrg
{
public:
	FontMrg();
	~FontMrg(){};
	static FontMrg * share();
	Font * getFont(std::string path,unsigned int size);

	void getDefualtFont();

private:
	static FontMrg * instance;
	std::map<std::string,Font *> fontList;
	Font *defualtFont;
};



#endif // !FONTMRG_H
