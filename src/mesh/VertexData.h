#pragma once
#ifndef VERTEXDATA_H
#define VERTEXDATA_H
#include"vec3.h"
#include"vec2.h"
class VertexData
{
public:
	VertexData();
	VertexData(vec3 &pos, vec2 &texcoords);
	VertexData(vec3 &pos, vec2 &texcoords, vec3 &nol);
	vec3 Pos;
	vec2 texCoords;
	vec3 normal;
};
#endif // !VERTEX_H
