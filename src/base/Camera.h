#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include"Node.h"

class Camera : public Node
{
public:
	Camera();
	~Camera() {};

	static Camera * createPerspective(float fovy, float aspect, float near, float far);
	static Camera * createOrtho(float left, float right, float bottom, float top, float near, float far);

	void setPerperspective(float fovy, float aspect, float near, float far);
	void setOrtho(float left, float right, float bottom, float top, float near, float far);

	mat4 getViewMatrix();
	mat4 getProjectionView();
	void lookAt(vec3 cameraTarget,vec3 up);


private:
	mat4 projection;
};
#endif // !CAMERA_H
