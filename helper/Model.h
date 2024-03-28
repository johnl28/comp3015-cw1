#pragma once
#include <vector>
#include <string>


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "glslprogram.h"
#include "Mesh.h"


class Model {

public:
	Model(const std::string& path);
	void Draw(GLSLProgram& program);

	void SetScale(float scale);
	void SetScale(const glm::vec3& scale);
	void SetPosition(const glm::vec3& pos);


	int GetMeshCount() { return static_cast<int>(m_Meshes.size()); }

	std::shared_ptr<Mesh> GetMesh(int index) 
	{ 
		if (index >= GetMeshCount())
		{
			return nullptr;
		}

		return m_Meshes[index]; 
	};

private:
	void LoadNode(const aiScene* scene, aiNode* node);
	void LoadMesh(const aiMesh* aiMesh, const aiMaterial* aiMaterial);
	void LoadTextures(const aiMaterial* aiMaterial, Mesh* mesh);

	Texture* LoadTexture(const std::string& path, TextureType type);

private:
	std::string m_FileName = "";
	std::vector<std::shared_ptr<Mesh>> m_Meshes;
};


