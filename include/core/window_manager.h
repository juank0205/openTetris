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

  bool Keys[1024] = {false};
private:
  bool m_isRunning;

  GLFWwindow *m_window;
  void startWindowLoop();
};
