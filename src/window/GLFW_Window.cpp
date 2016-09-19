#include "GLFW_Window.h"
#include"Connection.h"
#include"EventManager.h"

GLFW_Window::GLFW_Window()
{
}
static void error_callback(int error, const char* description)
{
	return;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		EventManager::share()->handleOnkeyPress(key);
		break;
	case GLFW_RELEASE:
		EventManager::share()->handleOnkeyRelease(key);
		break;
	default:
		break;
	}
	if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

static void mouse_button_callback(GLFWwindow* window,int button,int	action,int mods)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	switch (action)
	{
	case GLFW_PRESS:
		EventManager::share()->handleOnMousePress(button, vec2(xpos,ypos));
		break;
	case GLFW_RELEASE:
		EventManager::share()->handleOnMouseRelease(button, vec2(xpos, ypos));
		break;
	default:
		break;
	}
}
static void scroll_callback(GLFWwindow* window, double x, double y)
{
	EventManager::share()->handleOnScroll(x, y);
}

static void char_callback(GLFWwindow *window, unsigned int c)
{
	EventManager::share()->handleOnCharInput(c);
}

void GLFW_Window::init(const std::string title, GLuint w, GLuint h)
{
	width = w;
	height = h;
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
	//glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	windows = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
	glfwMakeContextCurrent(windows);
	glfwSetKeyCallback(windows, key_callback);
	glfwSetMouseButtonCallback(windows, mouse_button_callback);
	glfwSetScrollCallback(windows, scroll_callback);
	glfwSetCharCallback(windows, char_callback);
	Connection::share()->init(w,h);
}

void GLFW_Window::run()
{
	while (!glfwWindowShouldClose(windows))
	{
		glfwPollEvents();

		Connection::share()->update();

		glfwSwapBuffers(windows);
	}
	glfwDestroyWindow(windows);
	glfwTerminate();

}

GLuint GLFW_Window::getWidth() const
{
	return width;
}

GLuint GLFW_Window::getHeight() const
{
	return height;
}

void GLFW_Window::ifDecorated(bool i)
{
	glfwWindowHint(GLFW_DECORATED, i);
}

vec2 GLFW_Window::getSize() const
{
	return vec2(getWidth(),getHeight());
}
