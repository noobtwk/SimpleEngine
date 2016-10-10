#include "TextureCube.h"
#include<SOIL.h>

TextureCube::TextureCube(GLuint internalfomat, GLuint imagefomat, GLuint minfile, GLuint magfile, GLuint wsap_s, GLuint wsap_t, GLuint wsap_r)
{
	this->Internal_Format = internalfomat;
	this->Image_Fromat = imagefomat;
	this->MIN_FILE = minfile;
	this->MAG_FILE = magfile;
	this->WSAP_S = wsap_s;
	this->WSAP_T = wsap_t;
	this->WSAP_R = wsap_r;
}

TextureCube::~TextureCube()
{
}

TextureCube * TextureCube::createCube(const char * right, const char * left, const char * top, const char * bottom, const char * back, const char * front)
{
	auto tex = new TextureCube();
	tex->loadCube(right, left, top, bottom, back, front);
	return tex;
}

void TextureCube::loadCube(const char * right, const char * left, const char * top, const char * bottom, const char * back, const char * front)
{
	glGenTextures(1, &this->TextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID);

	int width, height;
	unsigned char *image;
	image = SOIL_load_image(right, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, this->Internal_Format, width, height, 0, this->Image_Fromat, GL_UNSIGNED_BYTE, image);
	image = SOIL_load_image(left, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+1, 0, this->Internal_Format, width, height, 0, this->Image_Fromat, GL_UNSIGNED_BYTE, image);
	image = SOIL_load_image(top, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+2, 0, this->Internal_Format, width, height, 0, this->Image_Fromat, GL_UNSIGNED_BYTE, image);
	image = SOIL_load_image(bottom, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+3, 0, this->Internal_Format, width, height, 0, this->Image_Fromat, GL_UNSIGNED_BYTE, image);
	image = SOIL_load_image(back, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+4, 0, this->Internal_Format, width, height, 0, this->Image_Fromat, GL_UNSIGNED_BYTE, image);
	image = SOIL_load_image(front, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+5, 0, this->Internal_Format, width, height, 0, this->Image_Fromat, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, this->MIN_FILE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, this->MAG_FILE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S , this->WSAP_S);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, this->WSAP_T);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, this->WSAP_R);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

}

