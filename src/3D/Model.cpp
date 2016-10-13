#include "Model.h"
#include"TextureManager.h"

Model::Model(const char * path)
{
	loadModel(path);
}

Model * Model::create(const char * path)
{
	auto model = new Model(path);
	model->initShader();
	model->setCamera(SceneManager::share()->getCurScene()->getFPCamera());
	model->initDepth();
	return model;
}

void Model::initShader()
{
	auto shader = ShaderManager::share()->creatOrAdd("H:/VS/game/shaders/model.vs", "H:/VS/game/shaders/model.frag");
	setShader(shader);
}

void Model::draw()
{
	for(int i=0;i<meshList.size();++i)
	{ 
		auto diff = materialList[i]->getDiffuseMap();
		RenderCommand com(meshList[i], getShader(), getCamera(), diff[0], getTransform(), getColor(), RenderCommand::Sprite3D);
		Render::share()->addRenderCommand(com);
	}
	
}

void Model::loadModel(string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "error: Assimp :" << importer.GetErrorString() << endl;
		return;
	}
	this->directory = path.substr(0, path.find_last_of('/'));

	this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshList.push_back(this->initMesh(mesh,scene));
	}
	for (int i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh* Model::initMesh(aiMesh * mesh, const aiScene * scene)
{
	auto m = new Mesh();
	vector<GLuint> indices;
	auto vernum = mesh->mNumVertices;
	vector<VertexData> vertices;

	AABB aabb;

	for (int i = 0; i < vernum; ++i)
	{
		VertexData t;
		if (!mesh->mTextureCoords[0])
		{
			 vertices.push_back(VertexData(vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z), vec2(0, 0),
				vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z)));
		}
		else
		{
			vertices.push_back(VertexData(vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z), vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y),
				vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z)));
		}
		
		aabb.add(vertices[i].pos);
	}
	setAABB(aabb);
	for (int i = 0; i < mesh->mNumFaces; ++i)
	{
		auto face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	m->addVertices(vertices);
	m->addIndice(indices);

	if (mesh->mMaterialIndex > 0)
	{
		auto material = scene->mMaterials[mesh->mMaterialIndex];

		auto m = new Material();
		vector<Texture2D*> diffuse = loadMaterialTex(material, aiTextureType_DIFFUSE);
		vector<Texture2D*> specular = loadMaterialTex(material, aiTextureType_SPECULAR);
		vector<Texture2D*> reflection = loadMaterialTex(material, aiTextureType_REFLECTION);
		vector<Texture2D*> height = loadMaterialTex(material, aiTextureType_HEIGHT);
		vector<Texture2D*> normal = loadMaterialTex(material, aiTextureType_NORMALS);
		vector<Texture2D*> ambient = loadMaterialTex(material, aiTextureType_AMBIENT);
		vector<Texture2D*> light = loadMaterialTex(material, aiTextureType_LIGHTMAP);
		vector<Texture2D*> shininess = loadMaterialTex(material, aiTextureType_SHININESS);
		vector<Texture2D*> displacement = loadMaterialTex(material, aiTextureType_DISPLACEMENT);
		m->setAmbientMap(ambient);
		m->setDiffuseMap(diffuse);
		m->setSpecularMap(specular);
		m->setReflectionMap(reflection);
		m->setHeighMap(height);
		m->setDisplacementMap(displacement);
		m->setLightMap(light);
		m->setNormalMap(normal);
		m->setShininessMap(shininess);
		materialList.push_back(m);
	}
	m->setNeetToCal(false);
	return m;
}

vector<Texture2D*> Model::loadMaterialTex(aiMaterial * m, aiTextureType type)
{
	vector<Texture2D*> tex;
	for (int i = 0; i < m->GetTextureCount(type); ++i)
	{
		aiString str;
		m->GetTexture(type, i, &str);
		string path(str.C_Str());
		path = directory + '/' + path;
		auto tex1 = TextureManager::share()->getOrCreateTex2D(path.c_str(), false);
		tex.push_back(tex1);
	}
	return tex;
}
