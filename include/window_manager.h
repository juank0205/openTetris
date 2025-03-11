#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input_manager.h"
#include "renderer.h"

class WindowManager {
public:
  WindowManager(int width, int height, const char *name);
  ~WindowManager();

  int createWindow();
private:
  int m_width;
  int m_height;
  const char *m_name;

  GLFWwindow *m_window;
  InputManager m_inputManager;
  Renderer m_renderer;

  void startWindowLoop();
};
