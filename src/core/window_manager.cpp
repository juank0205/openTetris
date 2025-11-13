#include "window_manager.h"
#include <iostream>

void frame_buffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

WindowManager::WindowManager() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void WindowManager::Clean() { glfwTerminate(); }

int WindowManager::CreateWindow(int width, int height, const char *name) {
  m_window = glfwCreateWindow(width, height, name, NULL, NULL);
  if (m_window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(m_window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }

  glfwSetFramebufferSizeCallback(m_window, frame_buffer_size_callback);
  m_isRunning = true;

  return 0;
}

void WindowManager::ClearColor() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowManager::PollEvents() { glfwPollEvents(); }

void WindowManager::SwapBuffers() { glfwSwapBuffers(m_window); }

void WindowManager::CheckWindowStatus() {
  if (glfwWindowShouldClose(m_window))
    m_isRunning = false;
}
