#pragma once
#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"

#include "helper/Camera.h"

class IslandScene: public Scene
{
public:
    IslandScene();
    void initScene();

    void update(float deltaTime);
    void render();
    void resize(int, int);

private:
    void compileShaders();
    void updateMVP(glm::mat4 model);

private:
    GLuint vaoHandle;
    GLSLProgram m_shaderProgram;
    Camera m_Camera;

    float angle = 0;
};

