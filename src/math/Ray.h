#pragma once
#ifndef RAY_H
#define RAY_H
#include"vec3.h"
#include"AABB.h"

enum Rayside
{
	up = 0,
	down,
	left,
	right,
	front,
	back
};

class Ray
{
public:
	Ray();
	Ray(vec3 origin, vec3 dir);
	~Ray();

	vec3 getOrigin();
	void setOrighin(vec3 ori);
	vec3 getDir();
	void setDirection(vec3 dir);

	bool isIntersectAABB(AABB aabb, Rayside *side, vec3 hitPoint);
	bool isIntersectTriangle(const vec3 &v1, const vec3 &v2, const vec3 &v3, float *out) const;


private:
	vec3 origin;
	vec3 direction;
};

#endif // !RAY_H
