#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include"Node.h"
class Camera :public Node
{
public:
	Camera();
	~Camera() {};

	static Camera * createPerperspective(float fovy, float aspect, float top, float near, float far);
	static Camera * createOrtho(float left, float right, float bottom, float top, float near, float far);

	void setPerperspective(float fovy, float aspect, float top, float near, float far);
	void setOrtho(float left, float right, float bottom, float top, float near, float far);

	mat4 getViewMatrix();
	mat4 getPorjectionMatrix();
	void lookAt();


private:
	mat4 projection;
};
#endif // !CAMERA_H
