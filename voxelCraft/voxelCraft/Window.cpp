#include "Window.h"

// standart includes
#include <iostream>

// opengl includes
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

GLFWwindow* Window::window;

int Window::initialize(int WIDTH, int HEIGHT, const char* title)
{
	// initialization GLFW.
	glfwInit();

	// Binding Window.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating Window.
	window = glfwCreateWindow(WIDTH, HEIGHT, title, nullptr, nullptr);

	// Testing Window.
	if (!window)
	{
		std::cerr << "Failed to initialize GLFW Window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Choosing Window.
	glfwMakeContextCurrent(window);

	// initialization GLEW.
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW!" << std::endl;
		return -1;
	}

	// Binding Viewport.
	glViewport(0, 0, WIDTH, HEIGHT);
	return 0;
}

bool Window::isShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::finalize()
{
	glfwTerminate();
}

void Window::setShouldClose(bool status)
{
	glfwSetWindowShouldClose(window, status);
}