#ifndef WINDOW_H
#define WINDOW_H
#include<glew.h>
#include<glfw3.h>
#include<string>
#include"vec2.h"

class GLFW_Window
{
public:
	GLFW_Window();
	
	void init(const std::string title,GLuint w,GLuint h);
	void run();
	GLuint getWidth() const;
	GLuint getHeight() const;
	void ifDecorated(bool i);
	vec2 getSize() const;

private:
	GLuint width;
	GLuint height;
	GLFWwindow* windows;
	
};

#endif // !WINDOW_H
