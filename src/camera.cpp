#include "camera.h"
#include "GLFW/glfw3.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"

static float lastFrame = glfwGetTime();

Camera::Camera(InputManager &inputManager)
    : m_position(glm::vec3(0.0f, 0.0f, 3.0f)),
      m_target(glm::vec3(0.0f, 0.0f, 0.0f)),
      m_cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
      m_cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)) {
  setView();
  inputManager.registerPressInput(GLFW_KEY_O, [&]() { this->moveForward(); });
  inputManager.registerPressInput(GLFW_KEY_L, [&]() { this->moveBackwards(); });
  inputManager.registerPressInput(GLFW_KEY_K, [&]() { this->moveLeft(); });
  inputManager.registerPressInput(GLFW_KEY_SEMICOLON,
                                  [&]() { this->moveRight(); });
}

Camera::~Camera() {}

void Camera::update(Program &program) { program.setMatrix4f("view", m_view); }

void Camera::setView() {
  m_view = glm::lookAt(m_position, m_cameraFront + m_position,
                       glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::moveLeft() {
  float newFrame = glfwGetTime();
  float deltaTime = newFrame - lastFrame;
  m_position -=
      glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed * deltaTime;
  setView();
  lastFrame = newFrame;
}

void Camera::moveRight() {
  float newFrame = glfwGetTime();
  float deltaTime = newFrame - lastFrame;
  m_position +=
      glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed * deltaTime;
  setView();
  lastFrame = newFrame;
}

void Camera::moveForward() {
  float newFrame = glfwGetTime();
  float deltaTime = newFrame - lastFrame;
  m_position += m_cameraFront * cameraSpeed * deltaTime;
  setView();
  lastFrame = newFrame;
}

void Camera::moveBackwards() {
  float newFrame = glfwGetTime();
  float deltaTime = newFrame - lastFrame;
  m_position -= m_cameraFront * cameraSpeed * deltaTime;
  setView();
  lastFrame = newFrame;
}
