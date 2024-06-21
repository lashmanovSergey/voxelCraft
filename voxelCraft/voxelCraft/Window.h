#pragma once

class GLFWwindow;

class Window
{
public:
	static GLFWwindow* window;
	static int initialize(int WIDTH, int HEIGHT, const char* title);
	static void finalize();
	static bool isShouldClose();
	static void swapBuffers();
	static void setShouldClose(bool status);
};

