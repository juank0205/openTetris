#include "open_gl_calls.h" //
#include "scene_manager.h"
#include "GLFW/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include "program.h"

static float lastFrame = glfwGetTime();

SceneManager::SceneManager(InputManager &inputManager)
    : m_camera(inputManager), m_projection(glm::mat4(1.0f)) {}

SceneManager::~SceneManager() {}

void SceneManager::setupScene() {
  m_projection =
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

  glm::vec3 cubePositions[] = {glm::vec3(0.0f, 0.0f, -10.0f),
                               glm::vec3(-3.0f, -3.0f, -10.0f)};

  Program &cuboProgram = m_resourceManager.getProgram("cubo");
  Program &lightingProgram = m_resourceManager.getProgram("lighting");
  float *vertices = m_resourceManager.getVerticesData("cubo");

  createGameObject(vertices, cuboProgram);
  m_gameObjects[0].translate(cubePositions[0]);

  createGameObject(vertices, lightingProgram);
  m_gameObjects[1].translate(cubePositions[1]);

  cuboProgram.useProgram();
  glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
  glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
  cuboProgram.setVec3f("objectColor", objectColor);
  cuboProgram.setVec3f("lightColor", lightColor);
  cuboProgram.setMatrix4f("projection", m_projection);

  lightingProgram.useProgram();
  lightingProgram.setMatrix4f("projection", m_projection);
}

void SceneManager::createGameObject(float *vertices, Program &program) {
  m_gameObjects.emplace_back(vertices, sizeof(float) * 36 * 6, nullptr, 0,
                             program);
  m_gameObjects[m_gameObjects.size() - 1].vao.bind();

  m_gameObjects[m_gameObjects.size() - 1].vbo.bind();
  glCall(m_gameObjects[m_gameObjects.size() - 1].vao.enable(
      0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0));
  glCall(m_gameObjects[m_gameObjects.size() - 1].vao.enable(
      1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 3 * sizeof(float)));
}

void SceneManager::update() {
  float thisFrame = glfwGetTime();
  float deltaTime = thisFrame - lastFrame;
  Program &cuboProgram = m_resourceManager.getProgram("cubo");

  m_camera.update(m_resourceManager, deltaTime);
  for (GameObject &go : m_gameObjects) {
    go.update(deltaTime);
  }

  glm::vec3 newPos = glm::vec3(3.0f * sin(thisFrame) * deltaTime,
                               3.0f * sin(thisFrame) * deltaTime,
                               3.0f * cos(thisFrame) * deltaTime);
  m_gameObjects[1].translate(newPos);
  cuboProgram.setVec3f("lightPos", newPos);
  lastFrame = thisFrame;
}
