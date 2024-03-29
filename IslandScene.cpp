#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "helper/scenerunner.h"
#include "IslandScene.h"


IslandScene::IslandScene()
{

}

void IslandScene::initScene()
{
    projection = glm::perspective(glm::radians(80.0f), (float)width / (float)height, 0.1f, 1000.0f);
    m_Camera.CameraPos.z = 5.0f;
    m_Camera.CameraPos.y = 5.0f;

    compileShaders();

    m_shaderProgram.printActiveUniforms();

    m_shaderProgram.use();
    m_shaderProgram.setUniform("u_FogParams.MinDist", 500.2f);
    m_shaderProgram.setUniform("u_FogParams.MaxDist", 1000.0f);
    m_shaderProgram.setUniform("u_FogParams.Color", glm::vec4(0.949f, 0.957f, 0.965f, 1.0f));

    m_LampShaderProgram.use();
    m_LampShaderProgram.setUniform("u_FogParams.MinDist", 500.2f);
    m_LampShaderProgram.setUniform("u_FogParams.MaxDist", 1000.0f);
    m_LampShaderProgram.setUniform("u_FogParams.Color", glm::vec4(0.949f, 0.957f, 0.965f, 1.0f));


    initLight();
    initModels();
}

void IslandScene::initModels()
{
    m_Model = new Model("media/models/FullPlatform-art.fbx");
    m_Model->SetScale(glm::vec3(0.2f));

    m_LampModel = new Model("media/models/shapes/cube.fbx");
    m_LampModel->SetScale(glm::vec3(0.05f));
}

void IslandScene::compileShaders()
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
    }
    catch (GLSLProgramException& e)
    {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}


void IslandScene::update(float time)
{
    UpdateCameraInput();
    UpdateCameraMouseInput();

    constexpr float radius = 150.0f;
    m_PointLights[0].Position.x = sin(time) * radius;
    m_PointLights[0].Position.z = cos(time) * radius;

    m_PointLights[1].Position.y = sin(time) * 20.0f;

    m_PointLights[2].Color.r = sin(time);
    m_PointLights[2].Color.g = tan(time);
    m_PointLights[2].Color.b = cos(time);
}

void IslandScene::UpdateCameraInput()
{
    const float cameraSpeed = m_Camera.Speed;
    auto& cameraPos = m_Camera.CameraPos;
    auto& cameraFront = m_Camera.CameraFront;
    auto& cameraUp = m_Camera.CameraUp;

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

void IslandScene::UpdateCameraMouseInput()
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

void IslandScene::initLight()
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
    randomPointLight.Intensity = 100.0f;
    m_PointLights.push_back(randomPointLight);
}

void IslandScene::renderLight()
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

        m_LampShaderProgram.use();
        m_LampShaderProgram.setUniform("u_LightColor", pointLight.Color);
        m_LampModel->SetPosition(pointLight.Position);
        m_LampModel->Draw(m_LampShaderProgram);
    }

}

void IslandScene::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    renderLight();


    m_shaderProgram.use();
    m_shaderProgram.setUniform("u_ViewPos", m_Camera.CameraPos);
    m_shaderProgram.setUniform("u_View", m_Camera.GetView());
    m_shaderProgram.setUniform("u_Projection", projection);

    m_shaderProgram.setUniform("u_ActivePointLights", static_cast<int>(m_PointLights.size()));

    m_Model->Draw(m_shaderProgram);

    m_Skybox.Draw(m_Camera, projection);
}

void IslandScene::resize(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, w, h);
}


