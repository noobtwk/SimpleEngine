#include"Frustum.h"
#include"Camera.h"

bool Frustum::initFrustumFromCamera(Camera* camera)
{
	_initialized = true;
	createPlane(camera);
	return true;
}

bool Frustum::initFrustumFromProjectMatrix(mat4 matrix)
{
	_initialized = true;
	createPlane(matrix);
	return true;
}

bool Frustum::isOutOfFrustum(const AABB& aabb) const
{
	if (_initialized)
	{
		vec3 point;

		int plane = _clipZ ? 6 : 4;
		for (int i = 0; i < plane; i++)
		{
			const vec3& normal = _plane[i].getNormal();
			point.setX(normal.x < 0 ? aabb.getMax().x : aabb.getMin().x);
			point.setY(normal.y < 0 ? aabb.getMax().y : aabb.getMin().y);
			point.setZ(normal.z < 0 ? aabb.getMax().z : aabb.getMin().z);

			if (_plane[i].getSide(point) == PointSide::FRONT_PLANE)
				return true;
		}
	}
	return false;
}

void Frustum::createPlane(Camera* camera)
{
	mat4 mat = camera->getProjectionView();
	//ref http://www.lighthouse3d.com/tutorials/view-frustum-culling/clip-space-approach-extracting-the-planes/
	//extract frustum plane
	float * m = mat.data();
	_plane[0].initPlane(-vec3(m[3] + m[0], m[7] + m[4], m[11] + m[8]), (m[15] + m[12]));//left
	_plane[1].initPlane(-vec3(m[3] - m[0], m[7] - m[4], m[11] - m[8]), (m[15] - m[12]));//right
	_plane[2].initPlane(-vec3(m[3] + m[1], m[7] + m[5], m[11] + m[9]), (m[15] + m[13]));//bottom
	_plane[3].initPlane(-vec3(m[3] - m[1], m[7] - m[5], m[11] - m[9]), (m[15] - m[13]));//top
	_plane[4].initPlane(-vec3(m[3] + m[2], m[7] + m[6], m[11] + m[10]), (m[15] + m[14]));//near
	_plane[5].initPlane(-vec3(m[3] - m[2], m[7] - m[6], m[11] - m[10]), (m[15] - m[14]));//far
}

void Frustum::createPlane(mat4 matrix)
{
	float * m = matrix.data();
	_plane[0].initPlane(-vec3(m[3] + m[0], m[7] + m[4], m[11] + m[8]), (m[15] + m[12]));//left
	_plane[1].initPlane(-vec3(m[3] - m[0], m[7] - m[4], m[11] - m[8]), (m[15] - m[12]));//right
	_plane[2].initPlane(-vec3(m[3] + m[1], m[7] + m[5], m[11] + m[9]), (m[15] + m[13]));//bottom
	_plane[3].initPlane(-vec3(m[3] - m[1], m[7] - m[5], m[11] - m[9]), (m[15] - m[13]));//top
	_plane[4].initPlane(-vec3(m[3] + m[2], m[7] + m[6], m[11] + m[10]), (m[15] + m[14]));//near
	_plane[5].initPlane(-vec3(m[3] - m[2], m[7] - m[6], m[11] - m[10]), (m[15] - m[14]));//far
}