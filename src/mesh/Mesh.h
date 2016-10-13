#pragma once
#ifndef MESH_H
#define MESH_H
#include<vector>
#include"VertexData.h"
#include<glew.h>
#include<glm.hpp>
#include<matrix_transform.hpp>
#include"mat4.h"
class Mesh
{
public:
	Mesh();
	~Mesh() {};
	void addIndex(unsigned int index);
	void addIndice(unsigned int *index, int size);
	void addIndice(std::vector<unsigned int> index);
	void addVertex(VertexData vertex);
	void addVertices(VertexData *vertex, int size);
	void addVertices(std::vector<VertexData> vertex);
	int getIndicesSize();
	int getVerticesSize();
	void setVAO(const GLuint &vao);
	GLuint getVAO();
	void setVBO(const GLuint &vbo);
	GLuint getVBO();
	void setEBO(const GLuint &ebo);
	GLuint getEBO();

	void Clear();
	void ClearIndices();
	void ClearVertices();

	void initRenderData();

	void merge(Mesh *m,mat4 mat);
	bool IfNeedToUpdate() const;
	bool IfNeedToCal() const;
	void setNeetToCal(bool i);

	void calNormal();

	std::vector<VertexData> getVertice();

private:
	std::vector<int> indices;
	std::vector<VertexData> vertices;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	bool needToUpdate;
	bool needToCalNorm;
};

#endif // !MESH_H
