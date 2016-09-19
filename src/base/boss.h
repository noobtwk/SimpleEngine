#pragma once
#ifndef BOSS_H
#define BOSS_H
#include"SceneManager.h"
#include"vec2.h"
#include"GLFW_Window.h"
#include"Render.h"

class GLFW_Window;
class Boss
{
public:
	Boss();
	~Boss() {};

	static Boss* share();

	void draw();

	GLFW_Window *getWin() const;

	void update(float delta);

	float getFPS();

	vec2 getWinSize() const;

	float getWinWidth() const;

	float getWinHeight() const;

	float getDeltatime();

	SceneManager* getSceneMrg();

private:
	static Boss* instance;
	GLFW_Window* window;

	float deltaTime;

};

#endif // !BOSS_H
