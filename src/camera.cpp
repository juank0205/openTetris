#include "camera.h"
#include "GLFW/glfw3.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include <iostream>

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
  inputManager.registerMouseOffsetCallback(
      [&](float x, float y) { this->updateAngles(x, y); });
}

Camera::~Camera() {}

void Camera::update(Program &program) {
  program.setMatrix4f("view", m_view);
  lastFrame = glfwGetTime();
}

void Camera::setView() {
  m_view = glm::lookAt(m_position, m_cameraFront + m_position,
                       glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::updateAngles(float offsetX, float offsetY) {
  m_yaw += offsetX;
  m_pitch -= offsetY;

  if (m_pitch >= 89.0f)
    m_pitch = 89.0f;
  if (m_pitch <= -89.0f)
    m_pitch = -89.0f;

  std::cout << "YAW: " << m_yaw << " PITCH: " << m_pitch << std::endl;

  calculateDirection();
  setView();
}

void Camera::calculateDirection() {
  glm::vec3 direction;
  direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  direction.y = sin(glm::radians(m_pitch));
  direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  m_cameraFront = glm::normalize(direction);
}

void Camera::moveLeft() {
  float newFrame = glfwGetTime();
  float deltaTime = newFrame - lastFrame;
  m_position -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) *
                m_cameraSpeed * deltaTime;
  setView();
  lastFrame = newFrame;
}

void Camera::moveRight() {
  float newFrame = glfwGetTime();
  float deltaTime = newFrame - lastFrame;
  m_position += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) *
                m_cameraSpeed * deltaTime;
  setView();
  lastFrame = newFrame;
}

void Camera::moveForward() {
  float newFrame = glfwGetTime();
  float deltaTime = newFrame - lastFrame;
  m_position += m_cameraFront * m_cameraSpeed * deltaTime;
  setView();
  lastFrame = newFrame;
}

void Camera::moveBackwards() {
  float newFrame = glfwGetTime();
  float deltaTime = newFrame - lastFrame;
  m_position -= m_cameraFront * m_cameraSpeed * deltaTime;
  setView();
  lastFrame = newFrame;
}
