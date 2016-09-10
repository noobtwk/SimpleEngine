#ifndef WINDOW_H
#define WINDOW_H
#include<glew.h>
#include<glfw3.h>
#include<string>

class GLFW_Window
{
public:
	GLFW_Window();
	
	void init(const std::string title,GLuint w,GLuint h);
	void run();


private:
	GLuint width;
	GLuint height;
	GLFWwindow* windows;
	
};

#endif // !WINDOW_H
