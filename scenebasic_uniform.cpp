#include "scenebasic_uniform.h"

#include <cstdio>
#include <cstdlib>

#include <glfw/glfw3.h>
#include <glm/glm.hpp>


#include <string>
using std::string;

#include <iostream>
using std::cerr;
using std::endl;

#include "helper/glutils.h"

using glm::vec3;

SceneBasic_Uniform::SceneBasic_Uniform() : angle(0.0f) {}

void SceneBasic_Uniform::initScene()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glPatchParameteri(GL_PATCH_VERTICES, 4);

    compile();
    projection = glm::perspective(glm::radians(80.0f), (float)width / (float)height, 0.1f, 1000.0f);
    m_Camera.CameraPos.z = 5.0f;
    m_Camera.CameraPos.y = 5.0f;


    m_shaderProgram.printActiveUniforms();

    m_shaderProgram.use();
    m_shaderProgram.setUniform("u_FogParams.MinDist", 500.2f);
    m_shaderProgram.setUniform("u_FogParams.MaxDist", 1000.0f);
    m_shaderProgram.setUniform("u_FogParams.Color", glm::vec4(0.949f, 0.957f, 0.965f, 1.0f));

    m_WaterShaderProgram.use();
    m_WaterShaderProgram.setUniform("u_FogParams.MinDist", 500.2f);
    m_WaterShaderProgram.setUniform("u_FogParams.MaxDist", 1000.0f);
    m_WaterShaderProgram.setUniform("u_FogParams.Color", glm::vec4(0.949f, 0.957f, 0.965f, 1.0f));

    m_LampShaderProgram.use();
    m_LampShaderProgram.setUniform("u_FogParams.MinDist", 500.2f);
    m_LampShaderProgram.setUniform("u_FogParams.MaxDist", 1000.0f);
    m_LampShaderProgram.setUniform("u_FogParams.Color", glm::vec4(0.949f, 0.957f, 0.965f, 1.0f));


    initLight();
    initModels();
}

void SceneBasic_Uniform::compile()
{
	try 
    {
        m_shaderProgram.compileShader("shader/island_scene.vert");
        m_shaderProgram.compileShader("shader/common.frag");
        m_shaderProgram.compileShader("shader/island_scene.frag");
        m_shaderProgram.link();

        m_LampShaderProgram.compileShader("shader/lamp.vert");
        m_LampShaderProgram.compileShader("shader/common.frag");
        m_LampShaderProgram.compileShader("shader/lamp.frag");
        m_LampShaderProgram.link();

        m_WaterShaderProgram.compileShader("shader/water.vert");
        m_WaterShaderProgram.compileShader("shader/water.tesc");
        m_WaterShaderProgram.compileShader("shader/water.tese");
        m_WaterShaderProgram.compileShader("shader/common.frag");
        m_WaterShaderProgram.compileShader("shader/island_scene.frag");
        m_WaterShaderProgram.link();


	} 
    catch (GLSLProgramException &e) 
    {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
    UpdateCameraInput();
    UpdateCameraMouseInput();

    m_WaterShaderProgram.use();
    m_WaterShaderProgram.setUniform("u_Time", t);


    constexpr float radius = 150.0f;
    m_PointLights[0].Position.x = sin(t) * radius;
    m_PointLights[0].Position.z = cos(t) * radius;

    m_PointLights[1].Position.y = sin(t) * 20.0f;

    m_PointLights[2].Color.r = (sin(t * 0.5) + 1.0f) * 0.5f;
    m_PointLights[2].Color.g = (cos(t * 0.7) + 1.0f) * 0.5f;
    m_PointLights[2].Color.b = (cos(t * 0.9) + 1.0f) * 0.5f;
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderLight();

    m_WaterShaderProgram.use();
    m_WaterShaderProgram.setUniform("u_ViewPos", m_Camera.CameraPos);
    m_WaterShaderProgram.setUniform("u_View", m_Camera.GetView());
    m_WaterShaderProgram.setUniform("u_Projection", projection);

    m_WaterShaderProgram.setUniform("u_ActivePointLights", static_cast<int>(m_PointLights.size()));

    m_Water->Draw(m_WaterShaderProgram, GL_PATCHES);

    m_shaderProgram.use();
    m_shaderProgram.setUniform("u_ViewPos", m_Camera.CameraPos);
    m_shaderProgram.setUniform("u_View", m_Camera.GetView());
    m_shaderProgram.setUniform("u_Projection", projection);

    m_shaderProgram.setUniform("u_ActivePointLights", static_cast<int>(m_PointLights.size()));

    m_Model->Draw(m_shaderProgram,GL_TRIANGLES);

    m_Skybox.Draw(m_Camera, projection);
}

void SceneBasic_Uniform::resize(int w, int h)
{
    width = w;
    height = h;
    glViewport(0,0,w,h);
}

void SceneBasic_Uniform::UpdateCameraInput()
{
    const float cameraSpeed = m_Camera.Speed;
    auto& cameraPos = m_Camera.CameraPos;
    auto& cameraFront = m_Camera.CameraFront;
    auto& cameraUp = m_Camera.CameraUp;

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, (m_WireframeMode = !m_WireframeMode) ? GL_LINE : GL_FILL);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * cameraFront;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}

void SceneBasic_Uniform::UpdateCameraMouseInput()
{
    static double lastX = 0.0, lastY = 0.0;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        double currX = 0.0, currY = 0.0;
        float& pitch = m_Camera.Pitch;
        float& yaw = m_Camera.Yaw;

        glfwGetCursorPos(window, &currX, &currY);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (!lastX && !lastY)
        {
            lastX = currX;
            lastY = currY;
        }

        auto xoffset = (currX - lastX) * m_Camera.Sensitivity;
        auto yoffset = (lastY - currY) * m_Camera.Sensitivity;

        lastX = currX;
        lastY = currY;

        if (pitch > 89.0f)
        {
            pitch = 89.0f;
        }
        else if (pitch < -89.0f)
        {
            pitch = -89.0f;
        }

        yaw += static_cast<float>(xoffset);
        pitch += static_cast<float>(yoffset);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
    {
        lastX = 0;
        lastY = 0;

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void SceneBasic_Uniform::initModels()
{
    m_Model = new Model("media/models/FullPlatform-art.fbx");
    m_Model->SetScale(glm::vec3(0.2f));

    m_LampModel = new Model("media/models/shapes/cube.fbx");
    m_LampModel->SetScale(glm::vec3(0.05f));

    m_Water = new Model("media/models/shapes/plane.obj");
    auto waterTexture = new Texture("media/textures/water.png");
    waterTexture->Type = TextureType::DIFFUSE;
    m_Water->GetMesh(0)->AddTexture(waterTexture);
    m_Water->SetScale(glm::vec3(800.0f));
    m_Water->SetPosition(vec3(0, -60, 0));
    
}

void SceneBasic_Uniform::initLight()
{
    PointLight pinkPointLight;
    pinkPointLight.Color = { 1.0f, 0.1f, 1.0f };
    pinkPointLight.Position = { 30.0f, 10.0f, 0.0f };
    pinkPointLight.Intensity = 500.0f;
    m_PointLights.push_back(pinkPointLight);

    PointLight whitePointLight;
    whitePointLight.Color = { 1.0f, 1.0f, 1.0f };
    whitePointLight.Position = { 30.0f, 5.0f, 150.0f };
    whitePointLight.Intensity = 500.0f;
    m_PointLights.push_back(whitePointLight);

    PointLight randomPointLight;
    randomPointLight.Color = { 0.0f, 1.0f, 0.0f };
    randomPointLight.Position = { -230.0f, 75.0f, 120.0f };
    randomPointLight.Intensity = 10.0f;
    m_PointLights.push_back(randomPointLight);
}

void SceneBasic_Uniform::renderLight()
{

    m_LampShaderProgram.use();
    m_LampShaderProgram.setUniform("u_View", m_Camera.GetView());
    m_LampShaderProgram.setUniform("u_Projection", projection);


    for (int i = 0; i < m_PointLights.size(); ++i)
    {
        const auto& pointLight = m_PointLights[i];

        m_shaderProgram.use();
        m_shaderProgram.setUniform(("u_PointLights[" + std::to_string(i) + "].Color").c_str(), pointLight.Color);
        m_shaderProgram.setUniform(("u_PointLights[" + std::to_string(i) + "].Position").c_str(), pointLight.Position);
        m_shaderProgram.setUniform(("u_PointLights[" + std::to_string(i) + "].Intensity").c_str(), pointLight.Intensity);

        m_WaterShaderProgram.use();
        m_WaterShaderProgram.setUniform(("u_PointLights[" + std::to_string(i) + "].Color").c_str(), pointLight.Color);
        m_WaterShaderProgram.setUniform(("u_PointLights[" + std::to_string(i) + "].Position").c_str(), pointLight.Position);
        m_WaterShaderProgram.setUniform(("u_PointLights[" + std::to_string(i) + "].Intensity").c_str(), pointLight.Intensity);

        m_LampShaderProgram.use();
        m_LampShaderProgram.setUniform("u_LightColor", pointLight.Color);
        m_LampModel->SetPosition(pointLight.Position);
        m_LampModel->Draw(m_LampShaderProgram,GL_TRIANGLES);
    }

}
