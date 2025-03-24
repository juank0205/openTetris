#pragma once

#include <GLFW/glfw3.h>

class InputManager {
public:
  InputManager();
  ~InputManager();

  void processInput(GLFWwindow *window);
};
