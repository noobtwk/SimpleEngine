#include "VertexData.h"

VertexData::VertexData() 
	:Pos(vec3()),texCoords(vec2()),normal(vec3())
{
}

VertexData::VertexData(vec3 & pos, vec2 & texcoords)
	:Pos(pos),texCoords(texcoords),normal(vec3(0.0f,0.0f,0.0f))
{
}

VertexData::VertexData(vec3 & pos, vec2 & texcoords, vec3 & nol)
{
	this->Pos = pos;
	this->normal = nol;
	this->texCoords = texcoords;
}
