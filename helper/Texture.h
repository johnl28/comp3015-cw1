#pragma once
#include <string>

#include <glad/glad.h>
#include "stb/stb_image.h"


struct Texture 
{
	GLuint Id = 0;

	std::string FilePath = "";

	int Width = 0;
	int Height = 0;
	int Channels = 0;


	Texture(const std::string& filePath): FilePath(filePath)
	{
		auto textureBuffer = stbi_load(filePath.c_str(), &Width, &Height, &Channels, 4);
		if (!textureBuffer)
		{
			return;
		}

		glGenTextures(1, &Id);
		glBindTexture(GL_TEXTURE_2D, Id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);
		stbi_image_free(textureBuffer);
	}

	~Texture()
	{
		glDeleteTextures(1, &Id);
	}

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
};


