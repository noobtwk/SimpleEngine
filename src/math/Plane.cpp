#include"Plane.h"
Plane::Plane()
	:
	_normal(0.f, 0.f, 1.f),
	_dist(0.f)
{

}

// create plane from tree point
Plane::Plane(const vec3 &p1, const vec3 &p2, const vec3 &p3)
{
	initPlane(p1, p2, p3);
}

// create plane from normal and dist
Plane::Plane(const vec3 &normal, float dist)
{
	initPlane(normal, dist);
}

// create plane from normal and a point on plane
Plane::Plane(const vec3 &normal, const vec3 &point)
{
	initPlane(normal, point);
}

void Plane::initPlane(const vec3 &p1, const vec3 &p2, const vec3 &p3)
{
	vec3 p21 = p2 - p1;
	vec3 p32 = p3 - p2;
	_normal = vec3::cross(p21, p32);
	_normal.normalize();
	_dist = vec3::dot(_normal, p1);
}

void Plane::initPlane(const vec3 &normal, float dist)
{
	float oneOverLength = 1 / normal.length();
	_normal = normal * oneOverLength;
	_dist = dist * oneOverLength;
}

void Plane::initPlane(const vec3 &normal, const vec3 &point)
{
	_normal = normal;
	_normal.normalize();
	_dist = vec3::dot(_normal, point);
}

float Plane::dist2Plane(const vec3 &p) const
{
	return vec3::dot(_normal, p) - _dist;
}


PointSide Plane::getSide(const vec3 &point) const
{
	float dist = dist2Plane(point);
	if (dist > 0)
		return PointSide::FRONT_PLANE;
	else if (dist < 0)
		return PointSide::BEHIND_PLANE;
	else
		return PointSide::IN_PLANE;
}
