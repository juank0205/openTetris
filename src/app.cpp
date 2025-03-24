#include "app.h"
#include <iostream>

App::App() : m_WindowManager(800, 600, "Vamos hijueputa") {}

App::~App() {}

void App::run() {
  std::cout << "Webos" << std::endl;
  m_sceneManager.setupScene();
  GLFWwindow *windowPointer = m_WindowManager.getWindowPointer();

  while (m_WindowManager.getIsRunning()) {
    m_inputManager.processInput(windowPointer);
    m_WindowManager.clearColor();
    m_renderer.render(m_sceneManager);
    m_WindowManager.swapBuffers();
    m_WindowManager.checkWindowStatus();
  }
}
