#include "Camera.h"

Camera::Camera()
{
}

Camera * Camera::createPerspective(float fovy, float aspect, float near, float far)
{
	auto c = new Camera();
	c->setPerperspective(fovy, aspect, near, far);
	c->initLookAt();
	c->updateFrustum();
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

void Camera::setProjection(mat4 proj)
{
	projection = proj;
}

mat4 Camera::getProjection()
{
	return projection;
}

mat4 Camera::getViewMatrix()
{
	return getTransform().inverse();
}

mat4 Camera::getViewWithoutMove()
{
	mat4 m = getTransform().inverse();
	auto data = m.data();
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	
	return m;
}

mat4 Camera::getProjectionView()
{
	return projection * getViewMatrix();
}

mat4 Camera::getSkyBoxProjectionView()
{
	return projection *getViewWithoutMove();
}

void Camera::lookAt(vec3 cameraTarget, vec3 up)
{
	auto aixZ = (position - cameraTarget);
	aixZ.normalize();
	auto aixX = vec3::cross(aixZ, up);
	aixX.normalize();

	auto aixY = vec3::cross(aixX, aixZ);
	aixY.normalize();
	rotate.fromAxises(aixX, aixY, aixZ);
	isNeedToUpdate = true;
	recache();
}

void Camera::initLookAt()
{
	setPosition(vec3(0,0,3));
	lookAt(vec3(), vec3(0, 1, 0));
}

void Camera::updateFrustum()
{
	if (getIsNeedToUpdate())
	{
		frustum.initFrustumFromCamera(this);
	}
}

bool Camera::isOutFrustum(AABB aabb)
{
	return frustum.isOutOfFrustum(aabb);
}

void Camera::update(float dt)
{
}
