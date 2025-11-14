#include "window_manager.h"
#include <iostream>

void frame_buffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode) {
  auto *wm = static_cast<WindowManager *>(glfwGetWindowUserPointer(window));
  if (!wm)
    return;

  // when a user presses the escape key, we set the WindowShouldClose property
  // to true, closing the application
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (key >= 0 && key < 1024) {
    if (action == GLFW_PRESS)
      wm->Keys[key] = true;
    else if (action == GLFW_RELEASE)
      wm->Keys[key] = false;
  }
}

WindowManager::WindowManager() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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

  glfwSetWindowUserPointer(m_window, this);
  glfwSetKeyCallback(m_window, key_callback);
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
