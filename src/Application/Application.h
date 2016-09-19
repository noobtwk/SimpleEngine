#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H
#include"twk.h"
class Application
{
public:
	Application();

	static Application * share();
	void run();


private:
	static Application * instance;
};

#endif // !APPLICATION_H
