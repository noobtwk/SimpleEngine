#pragma once
#ifndef RENDERBACKEND_H
#define RENDERBACKEND_H
#include<glew.h>
#include"RenderType.h"
class RenderBackEnd
{
public:
	RenderBackEnd();
	~RenderBackEnd() {};

	static RenderBackEnd* share();
	void genBuffer(unsigned int &V);
	void bindBuffer(RenderType::BufferType type,unsigned int V);
	void passData(RenderType::BufferType type,unsigned int size,const void * data);
	void bindTex(GLuint TexID,RenderType::TexType type);
	void passTex(GLuint TexUnitID, GLuint TexId, RenderType::TexType type);
	void activeTex(GLuint TexUnitsID);
	void bindVAO(GLuint vao);
	void drawElements(RenderType::DrawType type,GLuint size,GLvoid *indices);
	void drawArray(RenderType::DrawType type, GLuint first,GLuint size);

	void enableFuction(RenderType::Fuction type);
	void disableFuction(RenderType::Fuction type);
	void setDepthTestFuc(RenderType::DepthTestFuc type);
private:
	static RenderBackEnd *instance;

};

#endif // !RENDERBACKEND_H
