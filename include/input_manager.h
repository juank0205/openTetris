#pragma once

#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>

class InputManager {
public:
  InputManager();
  ~InputManager();

  void processInput(GLFWwindow *window);
  void registerPressInput(int key, std::function<void()> callback);

private:
  std::unordered_map<int, std::function<void()>> m_pressCallbacks;
};
