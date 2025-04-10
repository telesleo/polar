#include "texture.h"

#include <stb_image.h>
#include <glad/glad.h>
#include <iostream>

namespace polar
{
	Texture::Texture(char* path)
	{
		int width, height, nrChannels;
		uint8_t* data = stbi_load(path, &width, &height, &nrChannels, 0);

		if (!data)
		{
			std::cerr << "Failed to load texture: \#" << path << "\"" << std::endl;
		}

		glGenTextures(1, &_id);

		glBindTexture(GL_TEXTURE_2D, _id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}

	Texture::~Texture()
	{
		glDeleteBuffers(1, &_id);
	}

	void Texture::use() const
	{
		glBindTexture(GL_TEXTURE_2D, _id);
	}
}
