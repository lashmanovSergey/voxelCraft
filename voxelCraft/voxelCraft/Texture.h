#pragma once
#include "stb_image.h"
#include <iostream>

class Texture
{
public:
	unsigned int id;
	int width;
	int height;
	Texture(unsigned int texture, int width, int height);
	~Texture();

	void bind();
};

extern Texture* load_texture(std::string filename, int = 0);

