#pragma once

#include "input_manager.h"
#include "program.h"
#include <glm/glm.hpp>

class Camera {
public: 
  Camera(InputManager &inputManager);
  ~Camera();

  void update(Program &program);

  inline glm::mat4& getView() { return m_view; }

private:
  glm::vec3 m_position;
  glm::vec3 m_target;
  glm::mat4 m_view;
  glm::vec3 m_cameraFront;
  glm::vec3 m_cameraUp;
  float cameraSpeed = 2.0f;

  void setView();

  void moveLeft();
  void moveRight();
  void moveForward();
  void moveBackwards();
};
