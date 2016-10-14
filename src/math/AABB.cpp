#include "AABB.h"

AABB::AABB()
{
	empty();
}

AABB::~AABB()
{
}

void AABB::empty()
{
	const float N = 1e37f;
	max.x = max.y = max.z =-N;
	min.x = min.y = min.z = N;
}

void AABB::transform(mat4 matrix)
{
	vec3 corner[8];

	corner[0] = vec3(min.x, min.y, min.z);

	corner[1] = vec3(max.x, min.y, min.z);

	corner[2] = vec3(min.x, max.y, min.z);

	corner[3] = vec3(max.x, max.y, min.z);

	corner[4] = vec3(min.x, min.y, max.z);

	corner[5] = vec3(max.x, min.y, max.z);

	corner[6] = vec3(min.x, max.y, max.z);

	corner[7] = vec3(max.x, max.y, max.z);

	for (int i = 0; i < 8; ++i)
	{
		vec4 temp = vec4(corner[i], 1);
		temp =  matrix * temp;
		corner[i] = vec3(temp.x, temp.y, temp.z);
	}
	empty();
	add(corner,8);
}

void AABB::setMax(const vec3 & v)
{
	max = v;
}

void AABB::setMin(const vec3 & v)
{
	min = v;
}

vec3 AABB::getMin() const
{
	return min;
}

vec3 AABB::getMax() const
{
	return max;
}

void AABB::add(const vec3 & v)
{
	if (min.x > v.x)
		min.x = v.x;
	if (min.y > v.y)
		min.y = v.y;
	if (min.z > v.z)
		min.z = v.z;
	if (max.x < v.x)
		max.x = v.x;
	if (max.y < v.y)
		max.y = v.y;
	if (max.z < v.z)
		max.z = v.z;
}

void AABB::add(const vec3 * v, int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (min.x > v[i].x)
			min.x = v[i].x;

		if (min.y > v[i].y)
			min.y = v[i].y;
		
		if (min.z > v[i].z)
			min.z = v[i].z;

		if (max.x < v[i].x)
			max.x = v[i].x;
		
		if (max.y < v[i].y)
			max.y = v[i].y;
		
		if (max.z < v[i].z)
			max.z = v[i].z;
	}
}

void AABB::add(const AABB & box)
{
	min.x = (std::min(min.x, box.getMin().x));
	min.y = (std::min(min.y, box.getMin().y));
	min.z = (std::min(min.z, box.getMin().z));

	max.x = (std::max(max.x, box.getMax().x));
	max.y = (std::max(max.y, box.getMax().y));
	max.z = (std::max(max.z, box.getMax().z));
}

vec3 AABB::center() const
{
	return (max+min)/2;
}

bool AABB::isIntersect(const AABB & box, AABB * intersect)
{
	if (min.x > box.getMax().x) return false;
	if (max.x < box.getMin().x) return false;

	if (min.y > box.getMax().y) return false;
	if (max.y < box.getMin().y) return false;

	if (min.z > box.getMax().z) return false;
	if (max.z < box.getMin().z) return false;

	if (intersect != NULL)
	{
		intersect->min.x = std::max(min.x, box.getMin().x);
		intersect->max.x = std::min(max.x, box.getMax().x);

		intersect->min.y = std::max(min.y, box.getMin().y);
		intersect->max.y = std::min(max.y, box.getMax().y);

		intersect->min.z = std::max(min.z, box.getMin().z);
		intersect->max.z = std::min(max.z, box.getMax().z);
	}

	return true;
}

bool AABB::contains(const vec3 & v)
{
	if (min.x <=v.x && min.y<=v.y && min.z <= v.z && max.x >= v.x && max.y >= v.y && max.z >= v.z)
	{
		return true;
	}
	return false;
}

bool AABB::contains(const AABB & box)
{
	if (min.x <= box.getMin().x && min.y <= box.getMin().y && min.z <= box.getMin().z && max.x >= box.getMax().x && max.y >= box.getMax().y && max.z >= box.getMax().z)
	{
		return true;
	}
	return false;
}

std::vector<AABB> AABB::division(int depth,int k)
{
	std::vector<AABB> list;
	float s = pow(2, depth );
	float dtX = (k * (max.x - min.x) / s)/4;
	float dtY = (k * (max.y - min.y) / s)/4;
	float dtZ = (k * (max.z - min.z) / s)/4;

	auto cen = center();
	AABB a[8];

	a[0].add(cen + vec3(dtX, -dtY, -dtZ));
	a[0].add(vec3(min.x - dtX, max.y + dtY, max.z + dtZ));

	a[1].add(cen + vec3(-dtX, -dtY, -dtZ));
	a[1].add(vec3(max.x + dtX, max.y + dtY, max.z + dtZ));

	a[2].add(cen + vec3(dtX, -dtY, dtZ));
	a[2].add(vec3(min.x - dtX, max.y + dtY, min.z - dtZ));

	a[3].add(cen + vec3(-dtX, -dtY, dtZ));
	a[3].add(vec3(max.x + dtX, max.y + dtY, min.z - dtZ));

	a[4].add(cen + vec3(dtX, dtY, -dtZ));
	a[4].add(vec3(min.x - dtX, min.y - dtY, max.z + dtZ));

	a[5].add(cen + vec3(-dtX, dtY, -dtZ));
	a[5].add(vec3(max.x + dtX, min.y - dtY, max.z + dtZ));

	a[6].add(cen + vec3(dtX, dtY, dtZ));
	a[6].add(vec3(min.x - dtX, min.y - dtY, min.z - dtZ));

	a[7].add(cen + vec3(-dtX, dtY, dtZ));
	a[7].add(vec3(max.x + dtX, min.y - dtY, min.z - dtZ));

	for (int i = 0; i < 8; ++i)
	{
		list.push_back(a[i]);
	}
	
	return list;
}
