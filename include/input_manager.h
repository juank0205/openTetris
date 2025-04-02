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
  void registerMouseOffsetCallback(
      std::function<void(float offsetX, float offsetY)> callback);
  void registerMouseCallback(GLFWwindow *window);
  void setMouseValues(double mouseX, double mouseY);

private:
  std::unordered_map<int, std::function<void()>> m_pressCallbacks;
  std::function<void(float offsetX, float offsetY)> m_offsetCallback;
  double m_mouseX = 400.0;
  double m_mouseY = 300.0;
  bool m_firstMouse = true;
  const float m_sensitivity = 0.1f;
};
