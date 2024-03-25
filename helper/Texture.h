#pragma once
#include <string>
#include <iostream>

#include <glad/glad.h>
#include "stb/stb_image.h"


struct Texture 
{
	GLuint Id = 0;
	bool Loaded = false;

	std::string FilePath = "";

	int Width = 0;
	int Height = 0;
	int Channels = 0;


	Texture(const std::string& filePath): FilePath(filePath)
	{
		auto textureBuffer = stbi_load(filePath.c_str(), &Width, &Height, &Channels, 4);
		if (!textureBuffer)
		{
			std::cout << "Failed to load texture " << filePath << std::endl;
			return;
		}

		glGenTextures(1, &Id);
		glBindTexture(GL_TEXTURE_2D, Id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(textureBuffer);
		std::cout << "Loaded texture " << filePath << std::endl;
		Loaded = true;
	}

	~Texture()
	{
		glDeleteTextures(1, &Id);
	}

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
};


