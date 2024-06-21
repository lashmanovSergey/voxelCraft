#include "Shader.h"

#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>

#include <glew.h>
#include <glfw3.h>

Shader::Shader(unsigned int id) : id(id) 
{
	// TODO:...
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::use()
{
	glUseProgram(id);
}

Shader* load_shader(std::string vertexFile, std::string fragmentFile)
{
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// Checking for lost bits.
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	
	try
	{
		vShaderFile.open(vertexFile);
		fShaderFile.open(fragmentFile);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return nullptr;
	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	unsigned int fragment, vertex;
	int success;
	char logInfo[512];

	// Vertex Shader.
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, logInfo);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_ERROR" << std::endl;
		std::cerr << logInfo << std::endl;
		return nullptr;
	}

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, logInfo);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_ERROR" << std::endl;
		std::cerr << logInfo << std::endl;
		return nullptr;
	}

	// Shader Program
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, nullptr, logInfo);
		std::cerr << "ERROR::PROGRAM::LINK_ERROR" << std::endl;
		std::cerr << logInfo << std::endl;

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return nullptr;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return new Shader(program);
}