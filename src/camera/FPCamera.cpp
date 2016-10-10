#include "FPCamera.h"
#include"EventManager.h"
//#include<glfw3.h>
#include"boss.h"

FPCamera::FPCamera():speed(vec3(1,1,1)) ,front(0),back(0),left(0),right(0),first(true),sensitivity(0.1)
{
}

FPCamera::~FPCamera()
{
}

FPCamera * FPCamera::create(Camera * clone)
{
	auto camera = new FPCamera();
	camera->setPosition(clone->getPosition());
	camera->setProjection(clone->getProjection());
	camera->setScale(clone->getScale());
	camera->setRotateQ(clone->getRotateQ());
	EventManager::share()->addListener(camera);
	return camera;
}

bool FPCamera::onkeyPress(int keycode)
{
	if (keycode == GLFW_KEY_W)
	{
		front = 1;
	}
	if (keycode == GLFW_KEY_A)
	{
		left = 1;
	}
	if (keycode == GLFW_KEY_S)
	{
		back = 1;
	}
	if (keycode == GLFW_KEY_D)
	{
		right = 1;
	}
	return false;
}

bool FPCamera::onkeyRelease(int keycode)
{
	if (keycode == GLFW_KEY_W)
	{
		front = 0;
	}
	if (keycode == GLFW_KEY_A)
	{
		left = 0;
	}
	if (keycode == GLFW_KEY_S)
	{
		back = 0;
	}
	if (keycode == GLFW_KEY_D)
	{
		right = 0;
	}
	return false;
}

bool FPCamera::onMouseMove(vec2 pos)
{
	
	return false;
}

void FPCamera::update(float dt)
{
	double xpos, ypos;
	glfwGetCursorPos(Boss::share()->getWin()->getWin(),&xpos, &ypos);
	glfwSetCursorPos(Boss::share()->getWin()->getWin(), Boss::share()->getWinWidth() / 2, Boss::share()->getWinHeight() / 2);
	vec3 rotate = getRotateE();
	vec3 deltaPos = vec3(Boss::share()->getWinWidth() / 2 - xpos, Boss::share()->getWinHeight() / 2 - ypos, 0.0);

	rotate = rotate + vec3(deltaPos.y * sensitivity, deltaPos.x * sensitivity, 0.0);
	setRotateE(rotate);

	auto m = getTransform().data();
	vec3 frontDir(m[8], m[9], m[10]);
	vec3 leftDir(m[0], m[1], m[2]);

	vec3 pos = getPosition();
	pos +=  frontDir*speed.z *dt * -front;
	pos +=  frontDir* speed.z *dt * back;
	pos +=	leftDir*speed.x * dt * -left;
	pos +=	leftDir*speed.x * dt * right;

	setPosition(pos);
}

void FPCamera::setSpeed(vec3 s)
{
	speed = s;
}

vec3 FPCamera::getSpeed()
{
	return speed;
}
