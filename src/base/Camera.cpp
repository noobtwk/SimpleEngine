#include "Camera.h"

Camera::Camera()
{
}

Camera * Camera::createPerspective(float fovy, float aspect, float near, float far)
{
	auto c = new Camera();
	c->setPerperspective(fovy, aspect, near, far);
	return c;
}

Camera * Camera::createOrtho(float left, float right, float bottom, float top, float near, float far)
{
	auto c = new Camera();
	c->setOrtho(left, right, bottom, top, near, far);
	return c;
}

void Camera::setPerperspective(float fovy, float aspect, float near, float far)
{
	projection.perspective(fovy, aspect, near, far);
}

void Camera::setOrtho(float left, float right, float bottom, float top, float near, float far)
{
	projection.ortho(left, right, bottom, top, near, far);
}

mat4 Camera::getViewMatrix()
{
	return getTransform().inverse();
}

mat4 Camera::getProjectionView()
{
	return projection * getViewMatrix();
}

void Camera::lookAt(vec3 cameraTarget, vec3 up)
{
	auto aixZ = (cameraTarget - position);
	aixZ.normalize();
	auto aixX = vec3::cross(aixZ, up);
	aixX.normalize();

	auto aixY = vec3::cross(aixX, aixZ);
	aixY.normalize();
	rotate.fromAxises(aixX, aixY, aixZ);
	isNeedToUpdate = true;
	recache();
}
