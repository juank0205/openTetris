#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowManager {
public:
  WindowManager(int width, int height, const char *name);
  ~WindowManager();

  int createWindow();
  void swapBuffers();
  void checkWindowStatus();
  void clearColor();
  inline GLFWwindow *getWindowPointer() { return m_window; }
  inline const bool getIsRunning() const { return m_isRunning; }

private:
  int m_width;
  int m_height;
  bool m_isRunning;
  const char *m_name;

  GLFWwindow *m_window;

  void startWindowLoop();
};
