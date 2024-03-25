#include <iostream>

#include "Texture.h"
#include "Model.h"



Model::Model(const std::string& path)
{
    Assimp::Importer import;
    const aiScene * scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_PreTransformVertices);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    LoadNode(scene, scene->mRootNode);
}

void Model::Draw(GLSLProgram& program)
{
	for (auto& mesh : m_Meshes)
	{
		mesh->Draw(program);
	}
}

void Model::SetScale(const glm::vec3& scale)
{
	for (auto& mesh : m_Meshes)
	{
		mesh->SetScale(scale);
	}
}

void Model::LoadNode(const aiScene* scene, aiNode* node)
{
    for (unsigned int i = 0; i < node->mNumMeshes; ++i)
    {
        auto meshData = scene->mMeshes[node->mMeshes[i]];

        LoadMesh(meshData, scene->mMaterials[meshData->mMaterialIndex]);
    }

    for (unsigned int x = 0; x < node->mNumChildren; ++x)
    {
        LoadNode(scene, node->mChildren[x]);
    }
}

void Model::LoadMesh(const aiMesh* aiMesh, const aiMaterial* aiMaterial)
{

	std::vector<Vertex> vertices;

	for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
	{
		Vertex vertex;

		// Position
		vertex.Position = glm::vec3(aiMesh->mVertices[i].x, aiMesh->mVertices[i].y, aiMesh->mVertices[i].z);

		// Texture Coordinates
		if (aiMesh->HasTextureCoords(0))
		{
			vertex.TextureCoords = glm::vec2(aiMesh->mTextureCoords[0][i].x, aiMesh->mTextureCoords[0][i].y);
		}


		// Set Normals
		if (aiMesh->HasNormals())
		{
			vertex.Normal = glm::vec3(aiMesh->mNormals[i].x, aiMesh->mNormals[i].y, aiMesh->mNormals[i].z);
		}

		vertices.push_back(vertex);
	}


	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
	{
		const aiFace& face = aiMesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	auto mesh = new Mesh(vertices, indices);


	aiString texturePath;
	aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);

	if (texturePath.length)
	{
		std::string fullPath("media\\");
		fullPath.append(texturePath.C_Str());

		auto texture = new Texture(fullPath);
		if (texture->Loaded)
		{
			mesh->Texture = new Texture(fullPath);
		}
		else
		{
			delete texture;
		}
	}



	m_Meshes.push_back(mesh);
}
