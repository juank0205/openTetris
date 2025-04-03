#pragma once

#include "input_manager.h"
#include "resource_manager.h"

#include <glm/glm.hpp>

class Camera {
public: 
  Camera(InputManager &inputManager);
  ~Camera();

  void update(ResourceManager &resourceManager);

  inline glm::mat4& getView() { return m_view; }

private:
  glm::vec3 m_position;
  glm::vec3 m_target;
  glm::mat4 m_view;
  glm::vec3 m_cameraFront;
  glm::vec3 m_cameraUp;
  float m_cameraSpeed = 2.0f;
  float m_yaw = -90.0f;
  float m_pitch = 0.0f;

  void setView();
  void updateAngles(float offsetX, float offsetY);
  void calculateDirection();

  void moveLeft();
  void moveRight();
  void moveForward();
  void moveBackwards();
};
