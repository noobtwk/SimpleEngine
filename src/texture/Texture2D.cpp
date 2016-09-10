#include "Texture2D.h"
#include <iostream>
#include<SOIL.h>

Texture2D::Texture2D(GLuint internalfomat,GLuint imagefomat,GLuint minfile,GLuint magfile,
	GLuint wsap_s,GLuint wsap_t,GLuint wsap_r):Width(0), Height(0)
{
	this->Internal_Format = internalfomat;
	this->Image_Fromat = imagefomat;
	this->MIN_FILE = minfile;
	this->MAG_FILE = magfile;
	this->WSAP_S = wsap_s;
	this->WSAP_T = wsap_t;
	this->WSAP_R = wsap_r;
	glGenTextures(1, &this->TextureID);
}

Texture2D * Texture2D::createTexture2D(const char * path, GLuint internalfomat, GLuint imagefomat, bool ahp)
{
	auto tex = new Texture2D(path,ahp);
	return tex;
}

Texture2D::Texture2D(const char * path, bool ahp, GLuint internalfomat, GLuint imagefomat):Internal_Format(internalfomat),Image_Fromat(imagefomat),MIN_FILE(GL_NEAREST),MAG_FILE(GL_NEAREST)
,WSAP_R(0),WSAP_S(GL_REPEAT),WSAP_T(GL_REPEAT)
{
	glGenTextures(1, &this->TextureID);
	int width, height;
	if (ahp)
	{
		Internal_Format = GL_RGBA;
		Image_Fromat = GL_RGBA;
	}
	unsigned char *image = SOIL_load_image(path, &width, &height, 0, ahp ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	loadTexture2D(width, height, image);

	SOIL_free_image_data(image);

}
Texture2D::Texture2D(unsigned char * data,int w,int h, bool ahp) :Internal_Format(GL_RED), Image_Fromat(GL_RED), MIN_FILE(GL_NEAREST), MAG_FILE(GL_NEAREST)
, WSAP_R(0), WSAP_S(GL_CLAMP_TO_EDGE), WSAP_T(GL_CLAMP_TO_EDGE)
{
	loadTexture2D(w, h, data);
}



void Texture2D::loadTexture2D(GLuint width, GLuint height, unsigned char * data)
{
	Width = width;
	Height = height;
	glBindTexture(GL_TEXTURE_2D, this->TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0,this->Internal_Format , this->Width, this->Height, 0, this->Image_Fromat, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->MIN_FILE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->MAG_FILE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->WSAP_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->WSAP_T);
	if (this->WSAP_R)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->WSAP_R);
	}
	glBindTexture(GL_TEXTURE_2D, 0);


}

void Texture2D::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, this->TextureID);
}

vec2 Texture2D::getSize()
{
	return vec2(Width,Height);
}


