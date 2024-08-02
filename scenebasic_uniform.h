#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"

#include "helper/Camera.h"
#include "helper/Model.h"
#include "helper/Skybox.h"

#include "helper/PointLight.h"

class SceneBasic_Uniform : public Scene
{
private:
    GLuint vaoHandle;
    GLSLProgram prog;
    float angle;

    Skybox m_Skybox;

    GLSLProgram m_shaderProgram;
    GLSLProgram m_LampShaderProgram;

    Camera m_Camera;

    Model* m_Model = nullptr;
    Model* m_LampModel = nullptr;

    std::vector<PointLight> m_PointLights;

    void compile();

private:
    void UpdateCameraInput();
    void UpdateCameraMouseInput();

    void initLight();
    void renderLight();

    void initModels();

public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEBASIC_UNIFORM_H
