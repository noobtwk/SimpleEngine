#include "Cube.h"
#include"ShaderManager.h"
#include"RenderCommand.h"
#include"Render.h"

Cube::Cube() : depth(1.0f),height(1.0f),width(1.0f) 
{
}
 
Cube::~Cube()
{
}

Cube * Cube::create(float h, float w, float depth)
{
	auto cube = new Cube();
	cube->height = h;
	cube->width = w;
	cube->depth = depth;
	cube->setCamera(SceneManager::share()->getCurScene()->getFPCamera());
	cube->type = Type::col;
	cube->initMesh();
	cube->initShader();
	cube->initDepth();
	return cube;
}

Cube * Cube::createWithColor(float h, float w, float depth, vec3 col)
{
	auto cube = new Cube();
	cube->width = w;
	cube->height = h;
	cube->depth = depth;
	cube->setColor(col);
	cube->setCamera(SceneManager::share()->getCurScene()->getFPCamera());
	cube->type = Type::col;
	cube->initMesh();
	cube->initShader();
	cube->initDepth();
	return cube;
}

Cube * Cube::createWithColor(vec3 col)
{
	return createWithColor(1,1,1,col);
}

Cube * Cube::createWithTex(Texture2D * tex)
{
	auto cube = new Cube();
	cube->type = Type::tex1;
	cube->texture[0] = tex;
	cube->initMesh();
	cube->initShader();
	cube->initDepth();

	return cube;
}

Cube * Cube::createWithTex(const char * path,bool ahp)
{
	auto cube = new Cube();
	cube->texture[0] = new Texture2D(path, ahp);
	cube->type = Type::tex1;
	cube->setCamera(SceneManager::share()->getCurScene()->getFPCamera());
	cube->initMesh();
	cube->initShader();
	cube->initDepth();

	return cube;
}

Cube * Cube::createWithTex(Texture2D * top, Texture2D * bottom, Texture2D * size)
{
	auto cube = new Cube();
	cube->texture[0] = top;
	cube->texture[1] = bottom;
	cube->texture[2] = size;
	cube->setCamera(SceneManager::share()->getCurScene()->getFPCamera());
	cube->type = Type::tex3;
	cube->initMesh();
	cube->initShader();
	cube->initDepth();

	return cube;
}

Cube * Cube::createWithTex(const char * top, const char * bottom, const char * size,bool ahp)
{
	auto cube = new Cube();
	cube->texture[0] = new Texture2D(top, ahp);
	cube->texture[1] = new Texture2D(bottom, ahp);
	cube->texture[2] = new Texture2D(size, ahp);
	cube->type = Type::tex3;
	cube->setCamera(SceneManager::share()->getCurScene()->getFPCamera());
	cube->initMesh();
	cube->initShader();
	cube->initDepth();
	return cube;
}

void Cube::draw()
{
	if (type == Type::tex3)
	{
		for (int i = 0; i < 3; ++i)
		{
			RenderCommand com(mesh[i], getShader(), getCamera(),texture[i], getModel(), getColor(), getDepth(), true,RenderCommand::RenderType::Sprite3D);
			Render::share()->addRenderCommand(com);
		}
	}
	else if(type == Type::tex1)
	{
		RenderCommand com(mesh[0], getShader(), getCamera(), texture[0], getModel(), getColor(), getDepth(), true,RenderCommand::RenderType::Sprite3D);
		Render::share()->addRenderCommand(com);
	}
	else
	{
		RenderCommand com(mesh[0], getShader(), getCamera(), texture[0], getModel(), getColor(), getDepth(), false,RenderCommand::RenderType::Sprite3D);
		Render::share()->addRenderCommand(com);
	}
}

void Cube::initMesh()
{
	if (type == Type::tex3)
	{
		initTopMesh();
		initBottomMesh();
		initSizeMesh();
	}
	else
	{
		mesh[0] = new Mesh();
		VertexData vertices[]
		{
			{vec3(-0.5 * width , -0.5 * height , 0.5 * depth),vec2(0,0)},     //0
			{vec3(0.5 * width , -0.5 * height , 0.5 * depth) , vec2(1,0)},    //1
			{vec3(0.5 * width , 0.5 * height , 0.5 * depth) , vec2(1,1)},     //2
			{vec3(-0.5 * width, 0.5 * height, 0.5 * depth) ,vec2(0,1)},       //3

			{ vec3(-0.5 * width , -0.5 * height , -0.5 * depth),vec2(0,0) },  //4
			{ vec3(0.5 * width , -0.5 * height , -0.5 * depth) , vec2(1,0) }, //5
			{ vec3(0.5 * width , 0.5 * height , -0.5 * depth) , vec2(1,1) },  //6
			{ vec3(-0.5 * width, 0.5 * height, -0.5 * depth) ,vec2(0,1) },    //7

			{ vec3(-0.5 * width , -0.5 * height , -0.5 * depth),vec2(0,0) },  //8
			{ vec3(-0.5 * width , -0.5 * height , 0.5 * depth),vec2(1,0) },   //9
			{ vec3(-0.5 * width, 0.5 * height, 0.5 * depth) ,vec2(1,1) },     //10
			{ vec3(-0.5 * width , 0.5 * height , -0.5 * depth) , vec2(0,1) },  //11

			{ vec3(0.5 * width , -0.5 * height , 0.5 * depth) , vec2(0,0) },  //12
			{ vec3(0.5 * width , -0.5 * height , -0.5 * depth) , vec2(1,0) }, //13
			{ vec3(0.5 * width, 0.5 * height, -0.5 * depth) ,vec2(1,1) },    //14
			{ vec3(0.5 * width , 0.5 * height , 0.5 * depth) , vec2(0,1) },   //15

			{ vec3(-0.5 * width, 0.5 * height, 0.5 * depth) ,vec2(0,0) },     //16
			{ vec3(0.5 * width , 0.5 * height , 0.5 * depth) , vec2(1,0) },   //17
			{ vec3(0.5 * width, 0.5 * height, -0.5 * depth) ,vec2(1,1) },    //18
			{ vec3(-0.5 * width , 0.5 * height , -0.5 * depth) , vec2(0,1) },  //19

			{ vec3(-0.5 * width , -0.5 * height , 0.5 * depth),vec2(0,0) },   //20
			{ vec3(0.5 * width , -0.5 * height , 0.5 * depth) , vec2(1,0) },  //21
			{ vec3(0.5 * width , -0.5 * height , -0.5 * depth) , vec2(1,1) }, //22
			{ vec3(-0.5 * width , -0.5 * height , -0.5 * depth),vec2(0,1) }   //23

		};

		GLuint indices[]
		{
			0,1,2, 0,2,3,
			4,6,5, 4,7,6,
			8,9,10, 8,10,11,
			12,13,14, 12,14,15,
			16,17,18, 16,18,19,
			20,22,21, 20,23,22

		};
		mesh[0]->addVertices(vertices, sizeof(vertices) / sizeof(VertexData));
		mesh[0]->addIndice(indices, sizeof(indices) / sizeof(GLuint));

	}


}

void Cube::initTopMesh()
{
	mesh[0] = new Mesh();
	VertexData topVer[]
	{
		{ vec3(-0.5 * width , 0.5 * height ,0.5 *depth) ,vec2(0,0) },
		{ vec3(0.5*width ,0.5 *height , 0.5 *depth) ,vec2(1,0) },
		{ vec3(0.5 * width , 0.5 *height , -0.5 *depth) , vec2(1,1) },
		{ vec3(-0.5*width , 0.5 * height, -0.5 *depth) ,vec2(0,1) }
	};
	GLuint topIndex[]
	{
		0,1,2  ,0,2,3
	};
	mesh[0]->addVertices(topVer, sizeof(topVer) / sizeof(VertexData));
	mesh[0]->addIndice(topIndex, sizeof(topIndex) / sizeof(GLuint));
}

void Cube::initBottomMesh()
{
	mesh[1] = new Mesh();
	VertexData bottomVer[]
	{
		{vec3(-0.5 * width , -0.5 * height, 0.5 * depth) , vec2 (0,0)},
		{vec3(0.5 * width, -0.5 * height, 0.5 * depth) ,vec2(1,0)},
		{vec3(0.5 * width , -0.5 * height , -0.5 *depth), vec2(1,1)},
		{vec3(-0.5 * width , -0.5 * height , -0.5 * depth), vec2(0,1)}
	};
	GLuint indices[]
	{
		0,2,1, 0,3,2
	};
	mesh[1]->addIndice(indices, sizeof(indices) / sizeof(GLuint));
	mesh[1]->addVertices(bottomVer, sizeof(bottomVer) / sizeof(VertexData));
}

void Cube::initSizeMesh()
{
	mesh[2] = new Mesh();
	VertexData sizeVer[]
	{
		{ vec3(-0.5 * width , -0.5 * height , 0.5 * depth),vec2(0,0) },     //0
		{ vec3(0.5 * width , -0.5 * height , 0.5 * depth) , vec2(1,0) },    //1
		{ vec3(0.5 * width , 0.5 * height , 0.5 * depth) , vec2(1,1) },     //2
		{ vec3(-0.5 * width, 0.5 * height, 0.5 * depth) ,vec2(0,1) },       //3

		{ vec3(-0.5 * width , -0.5 * height , -0.5 * depth),vec2(0,0) },  //4
		{ vec3(0.5 * width , -0.5 * height , -0.5 * depth) , vec2(1,0) }, //5
		{ vec3(0.5 * width , 0.5 * height , -0.5 * depth) , vec2(1,1) },  //6
		{ vec3(-0.5 * width, 0.5 * height, -0.5 * depth) ,vec2(0,1) },    //7

		{ vec3(-0.5 * width , -0.5 * height , -0.5 * depth),vec2(0,0) },  //8
		{ vec3(-0.5 * width , -0.5 * height , 0.5 * depth),vec2(1,0) },   //9
		{ vec3(-0.5 * width, 0.5 * height, 0.5 * depth) ,vec2(1,1) },     //10
		{ vec3(-0.5 * width , 0.5 * height , -0.5 * depth) , vec2(0,1) },  //11

		{ vec3(0.5 * width , -0.5 * height , 0.5 * depth) , vec2(0,0) },  //12
		{ vec3(0.5 * width , -0.5 * height , -0.5 * depth) , vec2(1,0) }, //13
		{ vec3(0.5 * width, 0.5 * height, -0.5 * depth) ,vec2(1,1) },    //14
		{ vec3(0.5 * width , 0.5 * height , 0.5 * depth) , vec2(0,1) },   //15
	};
	GLuint indices[]
	{
		0,1,2, 0,2,3,
		4,6,5, 4,7,6,
		8,9,10, 8,10,11,
		12,13,14, 12,14,15,
	};
	mesh[2]->addIndice(indices, sizeof(indices) / sizeof(GLuint));
	mesh[2]->addVertices(sizeVer, sizeof(sizeVer) / sizeof(VertexData));
}

void Cube::initShader()
{
	if (type == Type::col)
	{
		auto shader = ShaderManager::share()->creatOrAdd("H:\\VS\\game\\shaders\\cube_color.vs", "H:\\VS\\game\\shaders\\cube_color.frag");
		setShader(shader);
	}
	else
	{
		auto shader = ShaderManager::share()->creatOrAdd("H:\\VS\\game\\shaders\\cube.vs", "H:\\VS\\game\\shaders\\cube.frag");
		setShader(shader);
	}
}

Mesh * Cube::getMesh()
{
	return mesh[0];
}
