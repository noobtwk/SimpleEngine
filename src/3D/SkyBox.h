#pragma once
#ifndef SKYBOX_H
#define SKYBOX_H
#include"Mesh.h"
#include"TextureManager.h"
#include"drawNode3D.h"

class SkyBox : public DrawNode3D
{
public:
	SkyBox();
	~SkyBox();

	static SkyBox *create(const char* right, const char* left, const char* top, const char* bottom, const char* back, const char* front);

	void initMesh();
	Mesh *getMesh();
	void initShader();
	void setCube(TextureCube* c);
	TextureCube* getCube();

	virtual void draw();
	
private:
	Mesh *mesh;
	TextureCube *cube;
};

#endif // !SKYBOX_H
