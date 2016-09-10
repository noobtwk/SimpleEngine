#include "Shader.h"
#include <iostream>
#include<fstream>
#include<sstream>


Shader::Shader(const char * vsPath, const char * fsPath)
{
	std::string vsCode;
	std::string fsCode;
	std::string gsCode;

	std::ifstream vsFile;
	std::ifstream fsFile;
	std::ifstream gsFile;
	try
	{
		vsFile.open(vsPath);
		fsFile.open(fsPath);

		std::stringstream vsStream, fsStream, gsStream;
		vsStream << vsFile.rdbuf();
		fsStream << fsFile.rdbuf();

		vsFile.close();
		fsFile.close();

		vsCode = vsStream.str();
		fsCode = fsStream.str();
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}

	const GLchar* vCode = vsCode.c_str();
	const GLchar* fCode = fsCode.c_str();

	GLuint vertex;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vCode, NULL);
	glCompileShader(vertex);
	checkCompileError(vertex, "VEXTURE");

	GLuint fragment;
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fCode, NULL);
	glCompileShader(fragment);
	checkCompileError(fragment, "FRAGMENT");


	this->program = glCreateProgram();
	glAttachShader(this->program, vertex);
	glAttachShader(this->program, fragment);

	glLinkProgram(this->program);
	checkCompileError(this->program, "PROGRAM");
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(this->program);
}

void Shader::Compile(const GLchar* vertexSource, const GLchar* fragSource)
{
	GLuint vertex;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);
	checkCompileError(vertex, "VEXTURE");

	GLuint fragment;
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragSource, NULL);
	glCompileShader(fragment);
	checkCompileError(fragment, "FRAGMENT");

	

	this->program = glCreateProgram();
	glAttachShader(this->program, vertex);
	glAttachShader(this->program, fragment);
	
	glLinkProgram(this->program);
	checkCompileError(this->program, "PROGRAM");
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::setFloat(const GLchar * name, GLfloat valuse, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform1f(glGetUniformLocation(this->program, name), valuse);
}

void Shader::setInt(const GLchar * name, GLint valuse, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform1i(glGetUniformLocation(this->program, name), valuse);
}

void Shader::setVector2f(const GLchar * name, GLfloat x, GLfloat y, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform2f(glGetUniformLocation(this->program,name), x, y);
}

void Shader::setVector2f(const GLchar * name, vec2 valuse, GLboolean useShader)
{
	if (useShader)
		this->Use();
	setVector2f(name, valuse.x, valuse.y, useShader);
}

void Shader::setVector3f(const GLchar * name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform3f(glGetUniformLocation(this->program, name), x, y, z);
}

void Shader::setVector3f(const GLchar * name, vec3 valuse, GLboolean useShader)
{
	if (useShader)
		this->Use();
	setVector3f(name, valuse.x, valuse.y, valuse.z, useShader);
}

void Shader::setVector4f(const GLchar * name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform4f(glGetUniformLocation(this->program, name), x, y, z, w);
}

void Shader::setVector4f(const GLchar * name, vec4 valuse, GLboolean useShader)
{
	if (useShader)
		this->Use();
	setVector4f(name, valuse.x, valuse.y, valuse.z, valuse.w, useShader);
}

void Shader::setMatrix4(const GLchar * name, mat4 valuse, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniformMatrix4fv(glGetUniformLocation(this->program, name), 1, GL_FALSE, valuse.data());
}

void Shader::setColor(const GLchar * name, vec3 valuse, GLboolean useShader)
{
	setVector3f(name, valuse, useShader);
}

void Shader::checkCompileError(GLuint object, std::string type)
{
	GLchar infoLog[1024];
	GLint success;
	if (type == "PROGRAM")
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout<< "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}


}

