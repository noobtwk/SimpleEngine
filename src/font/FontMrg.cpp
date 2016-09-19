#include "FontMrg.h"

FontMrg * FontMrg::instance = nullptr;

FontMrg::FontMrg()
{
	auto font = new Font("H:/VS/game/resource/font/simsun.ttc", 100);
}

FontMrg * FontMrg::share()
{
	if (!instance)
	{
		instance = new FontMrg();
	}
	return instance;
}

Font * FontMrg::getFont(std::string path, unsigned int size)
{
	char c[100];
	std::string s = path;
	_itoa_s(size, c, 10);
	s += c;
	auto f = fontList.find(path);
	if (f != fontList.end())
	{
		return fontList[s];
	}
	else
	{
		auto mfont = new Font(path, size);
		fontList[s] = mfont;
		return mfont;
	}
}

void FontMrg::getDefualtFont()
{
	defualtFont;
}
