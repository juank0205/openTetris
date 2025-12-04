#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>

/// Size of the input key array for keyboard handling
constexpr int KEYS_ARRAY_SIZE = 1024;

/**
 * @brief Initializes the OpenGL context.
 *
 * Must be called before creating a window or rendering anything.
 */
void init_gl_context();

/**
 * @brief Creates a GLFW window with a specified size and title.
 *
 * Also sets up a keyboard input array for tracking key states.
 *
 * @param width Width of the window in pixels.
 * @param height Height of the window in pixels.
 * @param name Window title.
 * @param keys Reference to a boolean array of size KEYS_ARRAY_SIZE to store key states.
 * @return Pointer to the created GLFWwindow.
 */
GLFWwindow *create_window(int width, int height, const char *name,
                          std::array<bool, KEYS_ARRAY_SIZE> &keys);

/**
 * @brief Swaps the front and back buffers of a window.
 *
 * Typically called once per frame to display the rendered scene.
 *
 * @param window Pointer to the GLFWwindow.
 */
void swap_buffers(GLFWwindow *window);

/**
 * @brief Checks if the window should close.
 *
 * @param window Pointer to the GLFWwindow.
 * @return true if the window is open, false if it should close.
 */
bool check_window_status(GLFWwindow *window);

/**
 * @brief Clears the color buffer with the current clear color.
 */
void clear_color();

/**
 * @brief Polls for and processes input and window events.
 *
 * Must be called every frame to update key states and handle window events.
 */
void poll_events();

/**
 * @brief Cleans up the OpenGL context and terminates GLFW.
 *
 * Should be called before program exit.
 */
void clean_gl_context();

