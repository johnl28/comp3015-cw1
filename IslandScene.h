#pragma once
#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"

#include "helper/Camera.h"
#include "helper/Model.h"
#include "helper/Skybox.h"

#include "helper/PointLight.h"

class IslandScene: public Scene
{
public:
    IslandScene();
    void initScene();

    void update(float deltaTime);
    void render();
    void resize(int, int);

private:
    void UpdateCameraInput();
    void UpdateCameraMouseInput();

    void initLight();
    void renderLight();

    void compileShaders();
    void initModels();

private:
    Skybox m_Skybox;

    GLSLProgram m_shaderProgram;
    GLSLProgram m_LampShaderProgram;

    Camera m_Camera;

    Model* m_Model = nullptr;
    Model* m_LampModel = nullptr;

    std::vector<PointLight> m_PointLights;
};

