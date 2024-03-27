#include <iostream>

#include "Model.h"
#include "Skybox.h"




Skybox::Skybox()
{
    CompileShaders();
	LoadModel();
}

void Skybox::Draw(Camera& camera, const glm::mat4& projection)
{
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_FRONT);


	m_ShaderProgram.use();
	m_ShaderProgram.setUniform("u_View", glm::mat4(glm::mat3(camera.GetView())));
	m_ShaderProgram.setUniform("u_Projection", projection);

	m_Mesh->Draw(m_ShaderProgram);


	glCullFace(GL_BACK);
	glDepthFunc(GL_LESS);
}


void Skybox::CompileShaders()
{
    try
    {
        m_ShaderProgram.compileShader("shader/skybox.vert");
        m_ShaderProgram.compileShader("shader/skybox.frag");
        m_ShaderProgram.link();
    }
    catch (GLSLProgramException& e)
    {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Skybox::LoadModel()
{
	auto model = new Model("media/models/shapes/cube.fbx");

	m_Mesh = model->GetMesh(0);
	if (!m_Mesh)
	{
		std::cerr << "Failed to load model for skybox" << std::endl;
		return;
	}

	delete model;
}
