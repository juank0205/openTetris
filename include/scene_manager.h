#pragma once

#include "game_object.h"

#include <vector>

class SceneManager {
public:
  SceneManager();
  ~SceneManager();

  void setupScene();

  inline const std::vector<GameObject> &getGameObjects() const { return m_gameObjects; }

private:
  std::vector<GameObject> m_gameObjects;
};
