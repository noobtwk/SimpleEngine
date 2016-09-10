#include "RenderBackEnd.h"


RenderBackEnd * RenderBackEnd::instance = nullptr;
RenderBackEnd::RenderBackEnd()
{
}
RenderBackEnd * RenderBackEnd::share()
{
	if (!instance)
	{
		instance = new RenderBackEnd();
	}
	return instance;
}

void RenderBackEnd::genBuffer(unsigned int &V)
{
	glGenBuffers(1, &V);
}

void RenderBackEnd::bindBuffer(RenderType::BufferType type, unsigned int V)
{
	switch (type)
	{
	case RenderType::BufferType::Indices:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, V);
		break;
	case RenderType::BufferType::Vertices:
		glBindBuffer(GL_ARRAY_BUFFER, V);
		break;
	default:
		break;
	}
}

void RenderBackEnd::passData(RenderType::BufferType type, unsigned int size, const void * data)
{
	switch (type)
	{
	case RenderType::BufferType::Indices:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		break;
	case RenderType::BufferType::Vertices:
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		break;
	default:
		break;
	}
}

void RenderBackEnd::bindTex( GLuint TexID, RenderType::TexType type)
{
	switch (type)
	{
	case RenderType::TexType::Tex2D:
		glBindTexture(GL_TEXTURE_2D, TexID);
		break;
	case RenderType::TexType::TexCube:
		glBindTexture(GL_TEXTURE_CUBE_MAP, TexID);
		break;
	default:
		break;
	}
}

void RenderBackEnd::passTex(GLuint TexUnitID, GLuint TexId, RenderType::TexType type)
{
	glActiveTexture(GL_TEXTURE0 + TexUnitID);
	bindTex(TexId, type);
}

void RenderBackEnd::activeTex(GLuint TexUnitsID)
{
	glActiveTexture(GL_TEXTURE0 + TexUnitsID);
}

void RenderBackEnd::bindVAO(GLuint vao)
{
	glBindVertexArray(vao);
}

void RenderBackEnd::drawElements(RenderType::DrawType type, GLuint size, GLvoid * indices)
{
	switch (type)
	{
	case RenderType::DrawType::TRI:
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, indices);
		break;
	case RenderType::DrawType::TRI_STRIP:
		glDrawElements(GL_TRIANGLE_STRIP, size, GL_UNSIGNED_INT, indices);
		break;
	default:
		break;
	}
}

void RenderBackEnd::drawArray(RenderType::DrawType type,GLuint first ,GLuint size)
{
	switch (type)
	{
	case RenderType::DrawType::TRI:
		glDrawArrays(GL_TRIANGLES, first, size);
		break;
	case RenderType::DrawType::TRI_STRIP:
		glDrawArrays(GL_TRIANGLE_STRIP, first, size);
		break;
	default:
		break;
	}
}

void RenderBackEnd::enableFuction(RenderType::Fuction type)
{
	switch (type)
	{
	case RenderType::Fuction::DepthTest:
		glEnable(GL_DEPTH_TEST);
		break;
	case RenderType::Fuction::Blend:
		glEnable(GL_BLEND);
		break;
	default:
		break;
	}
}

void RenderBackEnd::disableFuction(RenderType::Fuction type)
{
	switch (type)
	{
	case RenderType::Fuction::DepthTest:
		glDisable(GL_DEPTH_TEST);
		break;
	case RenderType::Fuction::Blend:
		glDisable(GL_BLEND);
		break;
	default:
		break;
	}
}

void RenderBackEnd::setDepthTestFuc(RenderType::DepthTestFuc type)
{
	switch (type)
	{
	case RenderType::DepthTestFuc::less:
		glDepthFunc(GL_LESS);
		break;
	case RenderType::DepthTestFuc::lessOrQua:
		glDepthFunc(GL_LEQUAL);
		break;
	default:
		break;
	}
}
