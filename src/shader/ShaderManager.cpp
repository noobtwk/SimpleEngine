#include "ShaderManager.h"

ShaderManager * ShaderManager::instance = nullptr;
ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

ShaderManager * ShaderManager::share()
{
	if (!instance)
	{
		instance = new ShaderManager();
	}
	return instance;
}

Shader * ShaderManager::creatOrAdd(const char * vs, const char * fs)
{
	Info info;
	info.vs = vs;
	info.fs = fs;
	auto f = list.find(info);
	if (f == list.end())
	{
		Shader * shader = new Shader(vs, fs);
		list[info] = shader;
		return shader;
	}
	else
		return list[info];
}

bool Info::operator<(const Info &i) const
{

	return fs < i.fs;
}


