#include "open_gl_calls.h"
#include "scene_manager.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/trigonometric.hpp"
#include "program.h"
#include "shader.h"

#include <iostream>

SceneManager::SceneManager(InputManager &inputManager)
    : m_camera(inputManager), m_projection(glm::mat4(1.0f)) {}

SceneManager::~SceneManager() {}

void SceneManager::setupScene() {
  {
    Shader vertex("res/shaders/vertex.vert", SHADER_TYPE_VERTEX);
    Shader fragment("res/shaders/fragment.frag", SHADER_TYPE_FRAGMENT);

    m_program.attachShader(vertex.getId());
    m_program.attachShader(fragment.getId());

    m_program.linkShaders();
  }

  float vertices[] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
                      0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, //
                      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
                      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
                      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
                      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //

                      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
                      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
                      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
                      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
                      -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, //
                      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //

                      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //
                      -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, //
                      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
                      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
                      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
                      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //

                      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
                      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
                      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
                      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
                      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, //
                      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //

                      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
                      0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, //
                      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
                      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
                      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
                      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //

                      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
                      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
                      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
                      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
                      -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, //
                      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

  // unsigned int indices[] = {0, 1, 2, 0, 2, 3};
  glm::vec3 cubePositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  for (auto &vector : cubePositions) {
    createGameObject(vertices);
    m_gameObjects[m_gameObjects.size() - 1].translate(vector);
  }

  std::cout << m_gameObjects.size() << std::endl;

  m_program.useProgram();
  m_program.set1Int("texture1", 0);
  m_program.set1Int("texture2", 1);

  Texture text2("res/textures/awesomeface.png", PNG);
  m_gameObjects[0].texture.activate(0);
  text2.activate(1);

  m_projection =
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

  m_program.setMatrix4f("view", m_camera.getView());
  m_program.setMatrix4f("projection", m_projection);
}

void SceneManager::createGameObject(float *vertices) {
  m_gameObjects.emplace_back(vertices, sizeof(float) * 36 * 5, nullptr, 0,
                             "res/textures/mortis.png", PNG, m_program);
  m_gameObjects[m_gameObjects.size() - 1].vao.bind();

  m_gameObjects[m_gameObjects.size() - 1].vbo.bind();
  m_gameObjects[m_gameObjects.size() - 1].texture.activate(0);
  glCall(m_gameObjects[m_gameObjects.size() - 1].vao.enable(
      0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0));
  glCall(m_gameObjects[m_gameObjects.size() - 1].vao.enable(
      1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 3 * sizeof(float)));
}

void SceneManager::update() { m_camera.update(m_program); }
