#include "Application.h"
#include"hello.h"
Application * Application::instance = nullptr;
Application::Application()
{
}

Application * Application::share()
{
	if (!instance)
	{
		instance = new Application();
	}
	return instance;
}

void Application::run()
{
	auto boss = Boss::share();
	auto window = boss->getWin();
	window->init("twk", 1600, 900);

	auto hello = Hello::create();
	boss->getSceneMrg()->setCurScene(hello);
	hello->init();


	window->run();

}
