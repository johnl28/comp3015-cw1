#pragma once
#include <string>
#include <iostream>

#include <glad/glad.h>
#include "stb/stb_image.h"


enum class TextureType {
	NONE = 0,
    DIFFUSE = 1,
    SPECULAR = 2,
    AMBIENT = 3,
    EMISSIVE = 4,
    HEIGHT = 5,
    NORMALS = 6,
    SHININESS = 7,
    OPACITY = 8,
    DISPLACEMENT = 9,
    LIGHTMAP = 10,
    REFLECTION = 11
};

struct Texture 
{
	GLuint Id = 0;
	bool Loaded = false;

	TextureType Type = TextureType::NONE;

	std::string FilePath = "";

	int Width = 0;
	int Height = 0;
	int Channels = 0;


	Texture(const std::string& filePath): FilePath(filePath)
	{

		glGenTextures(1, &Id);
		glBindTexture(GL_TEXTURE_2D, Id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		Load();
	}

	void Load()
	{
		auto textureBuffer = stbi_load(FilePath.c_str(), &Width, &Height, &Channels, 4);
		if (!textureBuffer)
		{
			Loaded = false;
			std::cout << "Failed to load texture " << FilePath << std::endl;
			return;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(textureBuffer);
		std::cout << "Loaded texture " << FilePath << std::endl;
		Loaded = true;
	}

	void Bind()
	{
		if (!Loaded)
		{
			throw std::runtime_error("Cannot bind unloaded texture");
		}

		glActiveTexture(GL_TEXTURE0 + (int)Type);
		glBindTexture(GL_TEXTURE_2D, Id);

	}

	~Texture()
	{
		glDeleteTextures(1, &Id);
	}

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
};


