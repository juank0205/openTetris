#include "input_manager.h"
#include "GLFW/glfw3.h"

InputManager::InputManager() {}
InputManager::~InputManager() {}

void InputManager::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
