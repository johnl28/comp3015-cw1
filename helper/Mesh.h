#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "glslprogram.h"
#include "Texture.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TextureCoords;
};


class Mesh {

public:
	Texture* Texture = nullptr;

	Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint> indices);

	void Draw(GLSLProgram& program);
	void SetScale(const glm::vec3& newScale) { m_Scale = newScale; }

	glm::mat4 GetTransform();


private:
	GLuint m_VAO = 0;
	GLuint m_VBO = 0;
	GLuint m_IBO = 0;

	glm::vec3 m_Scale = { 1.0f, 1.0f, 1.0f };
	glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };

    std::vector<GLuint> m_Indices;
	std::vector<Vertex> m_Vertices;


	// todo:
	// std::vector<Texture> m_Textures;
};


