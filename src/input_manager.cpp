#include "input_manager.h"
#include "GLFW/glfw3.h"

void mouseCallbackWrapper(GLFWwindow *window, double mouseX, double mouseY) {
  static_cast<InputManager *>(glfwGetWindowUserPointer(window))
      ->setMouseValues(mouseX, mouseY);
}

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

void InputManager::registerMouseCallback(GLFWwindow *window) {
  glfwSetWindowUserPointer(window, this);
  glfwSetCursorPosCallback(window, mouseCallbackWrapper);
}

void InputManager::registerMouseOffsetCallback(
    std::function<void(float offsetX, float offsetY)> callback) {
  m_offsetCallback = callback;
}

void InputManager::registerPressInput(int key, std::function<void()> callback) {
  m_pressCallbacks[key] = callback;
}

void InputManager::setMouseValues(double mouseX, double mouseY) {
  if (m_firstMouse) {
    m_mouseX = mouseX;
    m_mouseY = mouseY;
    m_firstMouse = false;
  }

  float offsetX = (mouseX - m_mouseX) * m_sensitivity;
  float offsetY = (mouseY - m_mouseY) * m_sensitivity;
  m_offsetCallback(offsetX, offsetY);
  m_mouseX = mouseX;
  m_mouseY = mouseY;
}
