#pragma once

#include "camera.h"
#include "game_object.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "input_manager.h"
#include "resource_manager.h"

#include <vector>

class SceneManager {
public:
  SceneManager(InputManager &inputManager);
  ~SceneManager();

  void setupScene();
  void update();

  inline std::vector<GameObject> &getGameObjects() { return m_gameObjects; }
  inline glm::mat4 &getViewMatrix() { return m_camera.getView(); }
  inline const glm::mat4 &getProjectionMatrix() const { return m_projection; }

private:
  std::vector<GameObject> m_gameObjects;
  Camera m_camera;
  glm::mat4 m_projection;
  ResourceManager m_resourceManager;

  void createGameObject(float *vertices, Program &program);
};
