#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glew.h>
#include <glm.hpp>
#include <type_ptr.hpp>
#include"vec2.h"
#include"vec3.h"
#include"vec4.h"
#include"mat4.h"

class Shader
{
public:
	Shader(const char* vsPath, const char *fsPath);

	void Use();
	GLuint program;

	void Compile(const GLchar* vertexSource, const GLchar* fragSource);

	void setFloat(const GLchar *name,GLfloat valuse,GLboolean useShader = false);
	void setInt(const GLchar *name, GLint valuse, GLboolean useShader = false);
	void setVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void setVector2f(const GLchar *name, vec2 valuse, GLboolean useShader = false);
	void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void setVector3f(const GLchar *name, vec3 valuse, GLboolean useShader = false);
	void setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void setVector4f(const GLchar *name, vec4 valuse, GLboolean useShader = false);
	void setMatrix4(const GLchar *name, mat4 valuse, GLboolean useShader = false);
	void setMatrix4f(const GLchar *name, glm::mat4 valuse, GLboolean useShader = false);
	void setColor(const GLchar *name, vec3 valuse, GLboolean useShader = false);

private:
	
	void checkCompileError(GLuint object, std::string type);
};


#endif // !SHADER_H
