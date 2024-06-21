#ifndef GLEW_STATIC
#define GLEW_STATIC

// standart includes
// ...

// opengl includes
#include <glew.h>
#include <glfw3.h>

// engines includes
#include "Shader.h" 
#include "Window.h"
#include "Events.h"
#include "Texture.h"

const int WIDTH = 800;
const int HEIGHT = 600;

float vertices[] =
{ // vertex coord's / texture coord's
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 0
	1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 1
	0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 2
	1.0f, 1.0f, 0.0f, 1.0f, 1.0f  // 3
};

unsigned int items[] =
{
	0, 1, 2,
	1, 2, 3
};

int main()
{
	// initialize: Window and Events system call_back's.
	Window::initialize(WIDTH, HEIGHT, "voxel_engine");
	Events::initialize();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Shader* shader = load_shader("main.glslv", "main.glslf");
	if (shader == nullptr)
	{
		std::cerr << "ERROR::SHADER::FAILED_TO_LOADING_SHADER" << std::endl;

		return 1;
	}

	Texture* texture = load_texture("stone.png");

	// VBO and VAO
	unsigned int VBO, VAO, EBO;

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(items), items, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLuint*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLuint*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Rendering...
	while (!Window::isShouldClose())
	{
		// ===> Events
		Events::pollEvents();
		if (Events::jpressed(GLFW_KEY_ESCAPE))
		{
			Window::setShouldClose(true);
		}
		if (Events::jclicked(GLFW_MOUSE_BUTTON_1))
		{
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		}

		// Rendeting one more...
		glClear(GL_COLOR_BUFFER_BIT);
		shader->use();
		texture->bind();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		Window::swapBuffers();
	}

	// finishing project.
	delete shader;
	delete texture;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	Window::finalize();
	return 0;
}
#endif