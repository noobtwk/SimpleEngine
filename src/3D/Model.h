#pragma once
#ifndef MODEL_H
#define MODEL_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <Importer.hpp> 
#include <scene.h>
#include <postprocess.h>
#include<vector>
#include"Material.h"
#include"Mesh.h"
using namespace std;
#include"drawNode3D.h"
#include"ShaderManager.h"
#include"RenderCommand.h"
#include"Render.h"
#include"SceneManager.h"
class Model:public DrawNode3D
{
public:
	Model(const char *path);
	static Model * create(const char* path);

	~Model() {};


	void initShader();

	virtual void draw();

private:
	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh* initMesh(aiMesh* mesh,const aiScene *scene);
	vector<Texture2D*> loadMaterialTex(aiMaterial *m, aiTextureType type);

	vector<Mesh*> meshList;
	vector<Material*> materialList;
	string directory;
};

#endif // !MODEL_H
