#pragma once
#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include<string>
#include<map>
#include"Shader.h"

struct Info
{
	std::string vs;
	std::string fs;
	bool operator < (const Info &i)const;
};
class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();
	
	static ShaderManager * share();
	Shader *creatOrAdd(const char * vs, const char *fs);

private:
	static ShaderManager *instance;
	std::map<Info, Shader*> list;
};

#endif // !SHADERMANAGER_H
