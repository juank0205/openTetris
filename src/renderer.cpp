#include "renderer.h"
#include "GLFW/glfw3.h"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::render(SceneManager &scene) {
  float thisFrame = glfwGetTime();
  for (GameObject &go : scene.getGameObjects()) {
    go.draw();
  }
  /*glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));*/
}
