#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>

#define KEYS_ARRAY_SIZE 1024

void init_gl_context();
GLFWwindow *create_window(int width, int height, const char *name,
                          std::array<bool, KEYS_ARRAY_SIZE> &keys);
void swap_buffers(GLFWwindow *window);
bool check_window_status(GLFWwindow *window);
void clear_color();
void poll_events();
void clean_gl_context();

// class WindowManager {
// public:
//   WindowManager();
//
//   int CreateWindow(int width, int height, const char *name);
//   void SwapBuffers();
//   void CheckWindowStatus();
//   void ClearColor();
//   void PollEvents();
//   void Clean();
//   std::array<bool, KEYS_ARRAY_SIZE> &GetKeys() { return keys; }
//   GLFWwindow *GetWindowPointer() { return m_window; }
//   [[nodiscard]] bool GetIsRunning() const { return m_isRunning; }
//
// private:
//   bool m_isRunning;
//   std::array<bool, KEYS_ARRAY_SIZE> keys = {false};
//   GLFWwindow *m_window;
//   void startWindowLoop();
// };
