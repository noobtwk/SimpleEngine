#include "SkyBox.h"
#include"ShaderManager.h"
#include"SceneManager.h"

SkyBox::SkyBox()
{
}

SkyBox::~SkyBox()
{
}

SkyBox * SkyBox::create(const char * right, const char * left, const char * top, const char * bottom, const char * back, const char * front)
{
	auto skybox = new SkyBox();
	auto c = TextureManager::share()->getOrCreateCube(right, left, top, bottom, back, front);
	skybox->setCube(c);
	skybox->initShader();
	skybox->initMesh();
	skybox->setCamera(SceneManager::share()->getCurScene()->getFPCamera());
	return skybox;
}

void SkyBox::initMesh()
{
	mesh = new Mesh();
	VertexData vertices[]{
		{ vec3(-1.0,1.0f,-1.0f),vec2()},
		{ vec3(-1.0,-1.0f,-1.0f),vec2() },
		{ vec3(1.0,-1.0f,-1.0f),vec2() },
		{ vec3(1.0,1.0f,-1.0f),vec2() },

		{ vec3(-1.0,-1.0f,1.0f),vec2() },
		{ vec3(-1.0,-1.0f,-1.0f),vec2() },
		{ vec3(-1.0,1.0f,-1.0f),vec2() },
		{ vec3(-1.0,1.0f,1.0f),vec2() },

		{ vec3(1.0,-1.0f,-1.0f),vec2() },
		{ vec3(1.0,-1.0f,1.0f),vec2() },
		{ vec3(1.0,1.0f,1.0f),vec2() },
		{ vec3(1.0,1.0f,-1.0f),vec2() },

		{ vec3(-1.0,-1.0f,1.0f),vec2() },
		{ vec3(-1.0,1.0f,1.0f),vec2() },
		{ vec3(1.0,1.0f,1.0f),vec2() },
		{ vec3(1.0,-1.0f,1.0f),vec2() },

		{ vec3(-1.0,1.0f,-1.0f),vec2() },
		{ vec3(1.0,1.0f,-1.0f),vec2() },
		{ vec3(1.0,1.0f,1.0f),vec2() },
		{ vec3(-1.0,1.0f,1.0f),vec2() },

		{ vec3(-1.0,-1.0f,-1.0f),vec2() },
		{ vec3(-1.0,-1.0f,1.0f),vec2() },
		{ vec3(1.0,-1.0f,-1.0f),vec2() },
		{ vec3(-1.0,-1.0f,1.0f),vec2() },
	};

	GLuint indices[]
	{
		0,1,2, 2,3,0,
		4,5,6, 6,7,4,
		8,9,10, 10,11,8,
		12,13,14, 14,15,12,
		16,17,18, 18,19,16,
		20,21,22, 22,23,20
	};
	mesh->addIndice(indices, sizeof(indices) / sizeof(GLuint));
	mesh->addVertices(vertices, sizeof(vertices) / sizeof(VertexData));
}

Mesh * SkyBox::getMesh()
{
	return mesh;
}

void SkyBox::initShader()
{
	auto shader = ShaderManager::share()->creatOrAdd("H:/VS/game/shaders/skybox.vs","H:/VS/game/shaders/skybox.frag");
	setShader(shader);
}

void SkyBox::setCube(TextureCube * c)
{
	cube = c;
}

TextureCube * SkyBox::getCube()
{
	return cube;
}

void SkyBox::draw()
{
}
