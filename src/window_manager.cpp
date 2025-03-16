#include <iostream>

#include "window_manager.h"
#include "renderer.h"

void frame_buffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

WindowManager::WindowManager(int width, int height, const char *name)
    : m_width(width), m_height(height), m_name(name), m_window(NULL) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

WindowManager::~WindowManager() { glfwTerminate(); }

int WindowManager::createWindow() {
  m_window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL);
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
  startWindowLoop();
  return 0;
}

void WindowManager::startWindowLoop() {
  Renderer m_renderer;
  m_renderer.setup();

  while (!glfwWindowShouldClose(m_window)) {
    m_inputManager.processInput(m_window);


    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_renderer.render();

    glfwSwapBuffers(m_window);
    glfwPollEvents();
  }
}
