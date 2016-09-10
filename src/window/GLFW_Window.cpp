#include "GLFW_Window.h"

GLFW_Window::GLFW_Window()
{
}
static void error_callback(int error, const char* description)
{
	return;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

static void mouse_button_callback(GLFWwindow* window,int button,int	action,int mods)
{

}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

}

static void scroll_callback(GLFWwindow* window, double x, double y)
{
	return;
}

static void char_callback(GLFWwindow *window, unsigned int c)
{

}

void GLFW_Window::init(const std::string title, GLuint w, GLuint h)
{
	width = w;
	height = h;
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
	glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	windows = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
	glfwMakeContextCurrent(windows);
	glfwSetKeyCallback(windows, key_callback);
	glfwSetCursorPosCallback(windows, cursor_position_callback);
	glfwSetMouseButtonCallback(windows, mouse_button_callback);
	glfwSetScrollCallback(windows, scroll_callback);
	glfwSetCharCallback(windows, char_callback);


}
