#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include"Node.h"
#include"Frustum.h"

class Camera : public Node
{
public:
	Camera();
	~Camera() {};

	static Camera * createPerspective(float fovy, float aspect, float near, float far);
	static Camera * createOrtho(float left, float right, float bottom, float top, float near, float far);

	void setPerperspective(float fovy, float aspect, float near, float far);
	void setOrtho(float left, float right, float bottom, float top, float near, float far);

	void setProjection(mat4 proj);
	mat4 getProjection();

	mat4 getViewMatrix();
	mat4 getViewWithoutMove();

	mat4 getProjectionView();

	mat4 getSkyBoxProjectionView();
	void lookAt(vec3 cameraTarget,vec3 up);

	void initLookAt();

	void updateFrustum();

	bool isOutFrustum(AABB aabb);

	virtual void update(float dt);

private:
	Frustum frustum;
	mat4 projection;
};
#endif // !CAMERA_H
