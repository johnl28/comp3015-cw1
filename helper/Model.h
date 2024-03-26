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

	void SetScale(const glm::vec3& scale);

private:
	void LoadNode(const aiScene* scene, aiNode* node);
	void LoadMesh(const aiMesh* aiMesh, const aiMaterial* aiMaterial);
	void LoadTextures(const aiMaterial* aiMaterial, std::vector<std::unique_ptr<Texture>>& textures);

	Texture* LoadTexture(const std::string& path, TextureType type);

private:
	std::string m_FileName = "";
	std::vector<Mesh*> m_Meshes;
};


