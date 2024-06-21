// Engine includes.
#include "Events.h"
#include "Window.h"

// Standart includes.
#include <iostream>

// OpenGL includes.
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

// Mouse 
#define _MOUSE_BUTTONS 1024

// Events data.
uint* Events::_frames;
bool* Events::_keys;
uint Events::_current = 0;
float Events::deltaX = 0.0f;
float Events::deltaY = 0.0f;
float Events::x = 0.0f;
float Events::y = 0.0f;
bool Events::_cursor_locked = false;
bool Events::_cursor_started = false;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	/* 
	Calculating deltaX and deltaY in order to calculate 
	the direction of movement of the cursor.
	*/
	if (Events::_cursor_started)
	{
		Events::deltaX = xpos - Events::x;
		Events::deltaY = ypos - Events::y;
	}
	else
	{
		Events::_cursor_started = true;
	}
	Events::x = xpos;
	Events::y = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
{
	/* Reading the click of the mouse button */
	if (action == GLFW_PRESS)
	{
		Events::_keys[_MOUSE_BUTTONS + button] = true;
		Events::_frames[_MOUSE_BUTTONS + button] = Events::_current;
	}
	else if (action == GLFW_RELEASE)
	{
		Events::_keys[_MOUSE_BUTTONS + button] = false;
		Events::_frames[_MOUSE_BUTTONS + button] == Events::_current;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	/* Reading the click of the keyboard button */
	if (action == GLFW_PRESS)
	{
		Events::_keys[key] = true;
		Events::_frames[key] = Events::_current;
	}
	else if (action == GLFW_RELEASE)
	{
		Events::_keys[key] = false;
		Events::_frames[key] = Events::_current;
	}
}

// Initialzie event-System...
int Events::initialize()
{
	GLFWwindow* window = Window::window;
	_keys = new bool[1032];
	_frames = new uint[1032];
	
	memset(_keys, false, 1032);
	memset(_frames, 0, 1032);

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	return 0;
}

void Events::pollEvents()
{
	glfwPollEvents();
}

bool Events::pressed(int keycode)
{
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
	{
		return false;
	}
	return _keys[keycode];
}

bool Events::jpressed(int keycode)
{
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
	{
		return false;
	}
	return _keys[keycode] && _frames[keycode] == _current;
}

bool Events::clicked(int button)
{
	int index = _MOUSE_BUTTONS + button;
	return _keys[index];
}

bool Events::jclicked(int button)
{
	int index = _MOUSE_BUTTONS + button;
	return _keys[index] && _frames[index] == _current;
}
