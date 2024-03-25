#pragma once
#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"

#include "helper/Camera.h"
#include "helper/Model.h"

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

    void compileShaders();
    void initModels();

private:

    GLuint vaoHandle;
    GLSLProgram m_shaderProgram;
    Camera m_Camera;

    float angle = 0;

    Model* m_Model = nullptr;
};

