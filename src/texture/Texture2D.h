#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glew.h>
#include"vec2.h"

class Texture2D
{
public:
	
	GLuint TextureID;
	GLuint Width, Height;
	GLuint Internal_Format;
	GLuint Image_Fromat;
	GLuint WSAP_S, WSAP_R, WSAP_T;
	GLuint MIN_FILE, MAG_FILE;


	Texture2D(GLuint internalfomat = GL_RGB, GLuint imagefomat = GL_RGB, GLuint minfile = GL_NEAREST, GLuint magfile = GL_NEAREST,
		GLuint wsap_s = GL_REPEAT, GLuint wsap_t = GL_REPEAT, GLuint wsap_r = 0);

	static Texture2D * createTexture2D(const char *path,GLuint internalfomat = GL_RGB,GLuint imagefomat=GL_RGB ,bool ahp = true);
	//static Texture2D * createTexture2D(unsigned char *data,int w,int h,GLuint internalfomat = GL_RGB, GLuint imagefomat = GL_RGB, bool ahp = true);
	Texture2D(const char *path, bool ahp = true, GLuint internalfomat =GL_RGB, GLuint imagefomat = GL_RGB);
	Texture2D(unsigned char * data, int w, int h, bool ahp = true);

	void loadTexture2D(GLuint width,GLuint height,unsigned char* data);
	void bindTexture();
	vec2 getSize();



};


#endif // !TEXTURE2D_H
