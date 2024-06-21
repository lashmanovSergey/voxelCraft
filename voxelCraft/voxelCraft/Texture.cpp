#include "Texture.h"
#include <glew.h>

Texture::Texture(unsigned int id, int width, int height) : id(id), width(width), height(height){}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

Texture* load_texture(std::string filename, int colors)
{
	int width, height, channels;
	const char* _filename = filename.c_str();
	unsigned char* image = stbi_load(_filename, &width, &height, &channels, colors);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return new Texture(texture, width, height);
}