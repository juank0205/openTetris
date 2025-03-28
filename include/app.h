#pragma once

#include "window_manager.h"
#include "renderer.h"
#include "scene_manager.h"
#include "input_manager.h"

class App {
public: 
  App();
  ~App();

  void run();

private:
  WindowManager m_WindowManager;
  InputManager m_inputManager;
  SceneManager m_sceneManager;
  Renderer m_renderer;
};
