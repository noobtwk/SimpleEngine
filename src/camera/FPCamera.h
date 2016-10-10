#pragma once
#ifndef FPCAMERA_H
#define FPCAMERA_H
#include"Camera.h"
#include"EventListener.h"


class FPCamera :public Camera ,public EventListener
{
public:
	FPCamera();
	~FPCamera();

	static FPCamera * create(Camera * clone);

	virtual bool onkeyPress(int keycode);
	virtual bool onkeyRelease(int keycode);
	//virtual bool onMousePress(int button, vec2 pos);
	virtual bool onMouseMove(vec2 pos);
	//virtual bool onMouseRelease(int button, vec2 pos);
	//virtual bool onScroll(int x, int y);

	virtual void update(float dt);

	void setSpeed(vec3 s);
	vec3 getSpeed();

private:
	vec3 speed;
	float sensitivity;
	float front;
	float back;
	float right;
	float left;
	bool first;
	vec3 lastPos;
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;

};

#endif // !FPCAMERA_H
