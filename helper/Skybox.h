#pragma once
#include "glslprogram.h"
#include "Model.h"
#include "Camera.h"

class Skybox {

public:
	Skybox();

	void Draw(Camera& camera, const glm::mat4& projection);

private:
	void CompileShaders();
	void LoadModel();

private:
	GLSLProgram m_ShaderProgram;

	std::shared_ptr<Mesh> m_Mesh = nullptr;


};


