
#include <glm/ext/matrix_transform.hpp>

#include "Mesh.h"


Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint> indices)
{
    m_Vertices = vertices;
    m_Indices = indices;

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TextureCoords));

    glBindVertexArray(0);
}

void Mesh::Draw(GLSLProgram& program)
{
    if (Texture)
    {
        Texture->Bind();

        program.setUniform("u_TextureDiffuse", (int)TextureType::DIFFUSE);
    }

    program.setUniform("u_Transform", GetTransform());

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

glm::mat4 Mesh::GetTransform()
{
    glm::mat4 transform(1.0f);

    transform = glm::rotate(transform, m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::rotate(transform, m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

    transform = glm::translate(transform, m_Position);
    transform = glm::scale(transform, m_Scale);

    return transform;
}
