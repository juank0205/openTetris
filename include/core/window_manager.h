#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowManager {
public:
  WindowManager();
  ~WindowManager() {};

  int CreateWindow(int width, int height, const char *name);
  void SwapBuffers();
  void CheckWindowStatus();
  void ClearColor();
  void PollEvents();
  void Clean();
  inline GLFWwindow *GetWindowPointer() { return m_window; }
  inline const bool GetIsRunning() const { return m_isRunning; }

private:
  bool m_isRunning;

  GLFWwindow *m_window;
  void startWindowLoop();
};
