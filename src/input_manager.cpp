#include "input_manager.h"
#include "GLFW/glfw3.h"

InputManager::InputManager() {}
InputManager::~InputManager() {}

void InputManager::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  for (auto &[key, callback] : m_pressCallbacks) {
    if (glfwGetKey(window, key) == GLFW_PRESS) {
      callback();
    }
  }
}

void InputManager::registerPressInput(int key, std::function<void()> callback) {
  m_pressCallbacks[key] = callback;
}
