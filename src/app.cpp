#include "app.h"

App::App() : m_WindowManager(800, 600, "Vamos hijueputa") {}

App::~App() {}

void App::run() {
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
