#pragma once

#include <iostream>

class Shader
{
public:
	unsigned int id;
	Shader(unsigned int id);
	~Shader();

	void use();
};

extern Shader* load_shader(std::string vertexFile, std::string fragmentFile);

