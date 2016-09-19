#include "connection.h"
#include"RenderBackEnd.h"
#include<time.h>
#include"boss.h"

Connection * Connection::instance = nullptr;

Connection::Connection()
{
}

Connection * Connection::share()
{
	if (!instance)
	{
		instance = new Connection();
	}
	return instance;
}

void Connection::init(unsigned int w, unsigned int h)
{
	RenderBackEnd::share()->init(w, h);

	curTicks = clock();
	preTicks = clock();
}

void Connection::update()
{
	curTicks = clock();
	float delta = (curTicks - preTicks)*1.0 / CLOCKS_PER_SEC;
	preTicks = curTicks;
	if (delta > 0.1)
	{
		isFirstFrame = false;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Boss::share()->update(delta);
}
