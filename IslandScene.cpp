#include <iostream>

#include "helper/scenerunner.h"
#include "IslandScene.h"

IslandScene::IslandScene()
{
    projection = glm::perspective(glm::radians(80.0f), (float) width / (float) height, 0.1f, 1000.0f);
    model = glm::mat4(1.0f);
}

void IslandScene::initScene()
{
    compileShaders();

    m_shaderProgram.printActiveUniforms();

    /////////////////// Create the VBO ////////////////////
    float positionData[] = {
        -0.8f, -0.8f, 0.0f,
         0.8f, -0.8f, 0.0f,
         0.0f,  0.8f, 0.0f };
    float colorData[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f };

    // Create and populate the buffer objects
    GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);

    // Create and set-up the vertex array object
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    glEnableVertexAttribArray(0);  // Vertex position
    glEnableVertexAttribArray(1);  // Vertex color


    glBindVertexBuffer(0, positionBufferHandle, 0, sizeof(GLfloat) * 3);
    glBindVertexBuffer(1, colorBufferHandle, 0, sizeof(GLfloat) * 3);

    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(0, 0);
    glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding(1, 1);
    glBindVertexArray(0);
}

void IslandScene::compileShaders()
{
    try
    {
        m_shaderProgram.compileShader("shader/island_scene.vert");
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

void IslandScene::updateMVP(glm::mat4 model)
{
    view = m_Camera.GetView();

    m_shaderProgram.setUniform("u_MVP", projection * view * model);
}

void IslandScene::update(float time)
{
    std::cout << time << std::endl;
    if(glfwGetKey(window, GLFW_KEY_W))
    {
        //model = glm::mat4(1.0f);
        model = glm::translate(model, { 0, 0, 1.0f * time });
        //model = glm::rotate(model, glm::radians(-10.0f * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    m_Camera.CameraPos.z += 0.5f * time;
}

void IslandScene::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updateMVP(model);

    glBindVertexArray(vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
}

void IslandScene::resize(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, w, h);
}


