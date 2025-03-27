#pragma once

#include "game_object.h"
#include "glm/ext/matrix_float4x4.hpp"

#include <vector>

class SceneManager {
public:
  SceneManager();
  ~SceneManager();

  void setupScene();

  inline std::vector<GameObject> &getGameObjects() { return m_gameObjects; }
  inline const glm::mat4 &getViewMatrix() const { return m_camera; }
  inline const glm::mat4 &getProjectionMatrix() const { return m_projection; }
private:
  std::vector<GameObject> m_gameObjects;
  glm::mat4 m_camera;
  glm::mat4 m_projection;
  Program m_program;

  void createGameObject(float *vertices);
};
