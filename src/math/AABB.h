#pragma once
#ifndef AABB_H
#define AABB_H
#include"vec3.h"
#include"mat4.h"
#include<algorithm>
class AABB
{
public:
	AABB();
	~AABB();

	void empty();
	void transform(mat4 matrix);
	void setMax(const vec3 &v);
	void setMin(const vec3 &v);
	vec3 getMin() const;
	vec3 getMax() const;
	void add(const vec3 &v);
	void add(const vec3 *v,int n);
	void add(const AABB &box);

	vec3 center() const;

	bool isIntersect(const AABB & box,AABB *intersect);
	bool contains(const vec3 &v);
	bool contains(const AABB &box);





private:
	vec3 max;
	vec3 min;
};

#endif // !AABB_H
