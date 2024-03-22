#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>



struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TextureCoords;
};


struct Mesh {
	GLuint Id = 0;


	Mesh(const std::vector<Vertex>& vertices)
	{
	

	}
};


