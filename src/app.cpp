#include "app.h"

App::App()
    : m_WindowManager(800, 600, "Vamos hijueputa"),
      m_sceneManager(m_inputManager) {}

App::~App() {}

void App::run() {
  m_sceneManager.setupScene();
  GLFWwindow *windowPointer = m_WindowManager.getWindowPointer();
  m_inputManager.registerMouseCallback(windowPointer);

  while (m_WindowManager.getIsRunning()) {
    m_inputManager.processInput(windowPointer);
    m_sceneManager.update();
    m_WindowManager.clearColor();
    m_renderer.render(m_sceneManager);
    m_WindowManager.swapBuffers();
    m_WindowManager.checkWindowStatus();
  }
}
