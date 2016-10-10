#pragma once
#ifndef TEXTURECUBE_H
#define TEXTURECUBE_H
#include<glew.h>
#include"Texture2D.h"
#include<vector>

class TextureCube : public Texture2D
{
public:

	TextureCube(GLuint internalfomat = GL_RGB, GLuint imagefomat = GL_RGB, GLuint minfile = GL_LINEAR, GLuint magfile = GL_LINEAR,
		GLuint wsap_s = GL_CLAMP_TO_EDGE, GLuint wsap_t = GL_CLAMP_TO_EDGE, GLuint wsap_r = GL_CLAMP_TO_EDGE);
	~TextureCube();

	static TextureCube *createCube(const char* right,const char* left,const char* top,const char* bottom,const char* back,const char* front);


	void loadCube(const char * right, const char * left, const char * top, const char * bottom, const char * back, const char * front);

private:
};

#endif // !TEXTURECUBE_H
