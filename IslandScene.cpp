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

    initModels();
}

void IslandScene::initModels()
{
    m_Model = new Model("media/source/Pirate Merchant Island.fbx");
    m_Model->SetScale(glm::vec3(1.0f));
}

void IslandScene::compileShaders()
{
    try
    {
        m_shaderProgram.compileShader("shader/island_scene.vert");
        m_shaderProgram.compileShader("shader/common.frag");
        m_shaderProgram.compileShader("shader/island_scene.frag");
        m_shaderProgram.link();
        m_shaderProgram.use();
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
    static bool firstMouse = true;
    static double lastX = 0, lastY = 0;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        double xpos, ypos;
        float &pitch = m_Camera.Pitch;
        float& yaw = m_Camera.Yaw;
        
        glfwGetCursorPos(window, &xpos, &ypos);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        auto xoffset = (xpos - lastX) * 0.1f;
        auto yoffset = (lastY - ypos) * 0.1f;

        lastX = xpos;
        lastY = ypos;

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
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstMouse = true;
    }
}

void IslandScene::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_shaderProgram.setUniform("u_Lights[0].Color", {1.0f, 1.0f, 1.0f});
    m_shaderProgram.setUniform("u_Lights[0].Position", m_Camera.CameraPos + 5.0f);

    m_shaderProgram.setUniform("u_ViewPos", m_Camera.CameraPos);
    m_shaderProgram.setUniform("u_View", m_Camera.GetView());
    m_shaderProgram.setUniform("u_Projection", projection);

    m_Model->Draw(m_shaderProgram);
}

void IslandScene::resize(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, w, h);
}


