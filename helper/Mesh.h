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

	Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint> indices);
	~Mesh();

	void Draw(GLSLProgram& program);
	void SetScale(const glm::vec3& newScale) { m_Scale = newScale; }
	void SetPosition(const glm::vec3& pos) { m_Position = pos; }

	void AddTexture(Texture* texture);

	GLuint GetVAO() { return m_VAO; }
	int GetIndicesCount() { return static_cast<int>(m_Indices.size()); }

	glm::mat4 GetTransform();

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

private:
	GLuint m_VAO = 0;
	GLuint m_VBO = 0;
	GLuint m_IBO = 0;

	glm::vec3 m_Scale = { 1.0f, 1.0f, 1.0f };
	glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };

    std::vector<GLuint> m_Indices;
	std::vector<Vertex> m_Vertices;


	std::vector<std::unique_ptr<Texture>> m_Textures;
};


