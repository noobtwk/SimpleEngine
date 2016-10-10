#include "Mesh.h"

Mesh::Mesh() :VAO(-1), VBO(-1), EBO(-1), needToUpdate(true), needToCalNorm(true)
{
}

void Mesh::addIndex(unsigned int index)
{
	indices.push_back(index);
}

void Mesh::addIndice(unsigned int *index,int size)
{
	for (int i = 0; i < size; ++i)
	{
		indices.push_back(index[i]);
	}
}

void Mesh::addVertex(VertexData vertex)
{
	vertices.push_back(vertex);
}

void Mesh::addVertices(VertexData *vertex,int size)
{
	for (int i = 0; i < size; ++i)
	{
		vertices.push_back(vertex[i]);
	}
}

int Mesh::getIndicesSize()
{
	return indices.size();
}

int Mesh::getVerticesSize()
{
	return vertices.size();
}

void Mesh::setVAO(const GLuint & vao)
{
	VAO = vao;
}

GLuint Mesh::getVAO()
{
	return VAO;
}

void Mesh::setVBO(const GLuint & vbo)
{
	VBO = vbo;
}

GLuint Mesh::getVBO()
{
	return VBO;
}

void Mesh::setEBO(const GLuint & ebo)
{
	EBO = ebo;
}

GLuint Mesh::getEBO()
{
	return EBO;
}

void Mesh::Clear()
{
	ClearIndices();
	ClearVertices();
}

void Mesh::ClearIndices()
{
	if(!indices.empty())
		indices.clear();
}

void Mesh::ClearVertices()
{
	if(!vertices.empty())
		vertices.clear();
}

void Mesh::initRenderData()
{
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, getVerticesSize()*sizeof(VertexData), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndicesSize()*sizeof(int), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(sizeof(vec3)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)(sizeof(vec3)+sizeof(vec2)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	needToUpdate = false;
}

void Mesh::merge(Mesh * m,mat4 mat)
{
	int offset = vertices.size();
	for (auto i : m->vertices)
	{
		vec4 t(i.Pos.x, i.Pos.y, i.Pos.z, 1.0f);
		auto res = mat * t;
		i.Pos = vec3(res.x, res.y, res.z);
		vertices.push_back(i);
	}
	for (auto i : m->indices)
	{
		indices.push_back(i + offset);
	}

}

bool Mesh::IfNeedToUpdate() const
{
	return needToUpdate;
}

bool Mesh::IfNeedToCal() const
{
	return needToCalNorm;
}

void Mesh::calNormal()
{
	int s = indices.size();
	for (int i = 0; i < s; i += 3)
	{
		int index0 = indices[i];
		int index1 = indices[i + 1];
		int index2 = indices[i + 2];
		vec3 v1 = vertices[index1].Pos-vertices[index0].Pos;
		vec3 v2 = vertices[index2].Pos - vertices[index0].Pos;
		vec3 normal = vec3::cross(v1, v2);
		normal.normalize();

		vertices[index0].normal += normal;
		vertices[index1].normal += normal;
		vertices[index2].normal += normal;
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].normal.normalize();
	}
	needToCalNorm = false;
}
