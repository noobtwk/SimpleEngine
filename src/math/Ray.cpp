#include "Ray.h"
#define EPSILON 0.000001

Ray::Ray()
{
}

Ray::Ray(vec3 origin, vec3 dir)
{
	this->origin = origin;
	this->direction = dir;
}

Ray::~Ray()
{
}

vec3 Ray::getOrigin()
{
	return origin;
}

void Ray::setOrighin(vec3 ori)
{
	this->origin = ori;
}

vec3 Ray::getDir()
{
	return direction;
}

void Ray::setDirection(vec3 dir)
{
	this->direction =dir;
}

bool Ray::isIntersectAABB(AABB aabb, Rayside * side, vec3 hitPoint)
{
	vec3 p;
	vec3 min = aabb.getMin();
	vec3 max = aabb.getMax();

	const vec3 &rayori = origin;
	const vec3 &raydir = direction;

	if (rayori.x > min.x && rayori.y > min.y && rayori.z > min.z && rayori.x < max.x && rayori.y < max.y && rayori.z < max.z)
		return true;

	float t;

	if (raydir.x != 0)
	{
		if (raydir.x > 0)
		{
			t = (min.x - rayori.x) / raydir.x;
		}
		else
			t = (max.x - rayori.x) / raydir.x;
		if (t > 0)
		{
			p = rayori + raydir * t;
			if (min.y < p.y && max.y >p.y && min.z < p.z && max.z > p.z)
			{
				hitPoint = p;
				if (side)
				{
					if (p.x<max.x)
						(*side) = Rayside::left;
					else
						(*side) = Rayside::right;
				}
				return true;
			}
		}
	}
	if (raydir.y != 0.f)
	{
		if (raydir.y > 0)
			t = (min.y - rayori.y) / raydir.y;
		else
			t = (max.y - rayori.y) / raydir.y;

		if (t > 0.f)
		{
			p = rayori + raydir * t;

			if (min.z < p.z && p.z < max.z && min.x < p.x && p.x < max.x)
			{
				hitPoint = p;
				if (side)
				{
					if (p.y<max.y)
						(*side) = Rayside::down;
					else
						(*side) = Rayside::up;
				}
				return true;
			}
		}
	}

	if (raydir.z != 0.f)
	{
		if (raydir.z > 0)
			t = (min.z - rayori.z) / raydir.z;
		else
			t = (max.z - rayori.z) / raydir.z;

		if (t > 0.f)
		{
			p = rayori + raydir * t;

			if (min.x < p.x && p.x < max.x && min.y < p.y && p.y < max.y)
			{
				hitPoint = p;
				if (side)
				{
					if (p.z<max.z)
						(*side) = Rayside::back;
					else
						(*side) = Rayside::front;
				}
				return true;
			}
		}
	}

	return false;
}

bool Ray::isIntersectTriangle(const vec3 & v1, const vec3 & v2, const vec3 & v3, float * out) const
{
	vec3 D = direction;
	vec3 e1, e2;  //Edge1, Edge2
	vec3 P, Q, T;
	float det, inv_det, u, v;
	float t;

	//Find vectors for two edges sharing V1
	e1 = v2 - v1;
	e2 = v3 - v1;
	//Begin calculating determinant - also used to calculate u parameter
	P = vec3::cross(direction, e2);
	//if determinant is near zero, ray lies in plane of triangle or ray is parallel to plane of triangle
	det = vec3::dot(e1, P);
	//NOT CULLING
	if (det > -EPSILON && det < EPSILON) return 0;
	inv_det = 1.f / det;

	//calculate distance from V1 to ray origin
	T = origin - v1;

	//Calculate u parameter and test bound
	u = vec3::dot(T, P) * inv_det;
	//The intersection lies outside of the triangle
	if (u < 0.f || u > 1.f) return 0;

	//Prepare to test v parameter
	Q = vec3::cross(T, e1);

	//Calculate V parameter and test bound
	v = vec3::dot(D, Q) * inv_det;
	//The intersection lies outside of the triangle
	if (v < 0.f || u + v  > 1.f) return 0;

	t = vec3::dot(e2, Q) * inv_det;

	if (t > EPSILON) { //ray intersection
		if (out) *out = t;
		return true;
	}

	// No hit, no win
	return false;
}
