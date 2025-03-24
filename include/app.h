#pragma once

#include "renderer.h"
#include "window_manager.h"
#include "scene_manager.h"
#include "input_manager.h"

class App {
public: 
  App();
  ~App();

  void run();

private:
  WindowManager m_WindowManager;
  SceneManager m_sceneManager;
  Renderer m_renderer;
  InputManager m_inputManager;
};
