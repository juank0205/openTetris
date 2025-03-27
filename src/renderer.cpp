#include "renderer.h"
#include "GLFW/glfw3.h"

static float lastFrame = glfwGetTime();

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::render(SceneManager &scene) {
  float thisFrame = glfwGetTime();
  for (GameObject &go : scene.getGameObjects()) {
    go.draw(thisFrame - lastFrame);
  }
  lastFrame = thisFrame;
  /*glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));*/
}
