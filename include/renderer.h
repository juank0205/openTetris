#pragma once

#include "scene_manager.h"

class Renderer {
public:
  Renderer();
  ~Renderer();

  void render(SceneManager &scene);
};
