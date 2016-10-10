#pragma once
#ifndef CUBE_H
#define CUBE_H
#include"drawNode3D.h"
#include"Texture2D.h"
#include"Mesh.h"
#include"SceneManager.h"


class Cube :public DrawNode3D
{
	enum Type
	{
		col,
		tex1,
		tex3
	};
public:
	Cube();
	~Cube();
	static Cube * create(float h, float w, float depth);
	static Cube * createWithColor(float h, float w, float depth, vec3 col);
	static Cube * createWithColor(vec3 col);
	static Cube * createWithTex(Texture2D *tex);
	static Cube * createWithTex(const char * path,bool ahp);
	static Cube * createWithTex(Texture2D *top, Texture2D *bottom, Texture2D *size);
	static Cube * createWithTex(const char * top, const char * bottom, const char * size,bool ahp);

	virtual void draw();

	void initMesh();
	void initTopMesh();
	void initBottomMesh();
	void initSizeMesh();

	void initShader();

	Mesh *getMesh();

private:
	float height;
	float width;
	float depth;
	vec3 color;
	Texture2D * texture[3];
	Mesh *mesh[3];
	Type type;
};


#endif // !CUBE_H
