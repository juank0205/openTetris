#include "window_manager.h"
#include "logger.h"

#include <GLFW/glfw3.h>
#include <array>
#include <cstdint>

enum class OpenGLVersion : std::uint8_t { Major = 4, Minor = 5 };

namespace {

void frame_buffer_size_callback(GLFWwindow *window, int width, // NOLINT
                                int height) {
  glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, // NOLINT
                  int action,                                // NOLINT
                  int mode) {                                // NOLINT
  bool *keys = static_cast<bool *>(glfwGetWindowUserPointer(window));
  if (keys == nullptr) {
    return;
  }

  // when a user presses the escape key, we set the WindowShouldClose property
  // to true, closing the application
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
  if (key >= 0 && key < KEYS_ARRAY_SIZE) {
    if (action == GLFW_PRESS) {
      keys[key] = true;
    } else if (action == GLFW_RELEASE) {
      keys[key] = false;
    }
  }
}
} // namespace

void init_gl_context() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,
                 static_cast<int>(OpenGLVersion::Major));
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,
                 static_cast<int>(OpenGLVersion::Minor));
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void clean_gl_context() { glfwTerminate(); }

GLFWwindow *create_window(int width, int height, const char *name,
                          std::array<bool, KEYS_ARRAY_SIZE> &keys) {
  GLFWwindow *window = glfwCreateWindow(width, height, name, nullptr, nullptr);
  if (window == nullptr) {
    LOG_CRITICAL("Failed to initialize GLFW");
    glfwTerminate();
    return nullptr;
  }
  glfwMakeContextCurrent(window);

  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == GL_FALSE) {
    LOG_CRITICAL("Failed to initialize GLAD");
  }

  glfwSetWindowUserPointer(window, keys.data());
  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

  LOG_TRACE("Window created! x: {0}, y: {0}", width, height);
  return window;
}

void clear_color() {
  glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void poll_events() { glfwPollEvents(); }

void swap_buffers(GLFWwindow *window) { glfwSwapBuffers(window); }

bool check_window_status(GLFWwindow *window) {
  return glfwWindowShouldClose(window) == GL_FALSE;
}
