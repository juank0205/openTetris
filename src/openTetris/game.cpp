#include "game.h"
#include "resource_manager.h"
#include "shader.h"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>

Game::Game(float width, float height, const char *window_name)
    : width(width), height(height), window_name(window_name) {}

void Game::Setup() {
  this->window_manager.CreateWindow(this->width, this->height,
                                    this->window_name);
  this->sprite_renderer.InitRenderData();

  this->resource_manager.LoadShader(
      "res/shaders/sprite.vert", "res/shaders/sprite.frag", nullptr, "sprite");
  glm::mat4 projection =
      glm::ortho(0.0f, this->width, this->height, 0.0f, -1.0f, 1.0f);
  ShaderProgram &spriteShader = this->resource_manager.GetShader("sprite");
  spriteShader.SetInteger("image", 0, true); // Uses shader
  spriteShader.SetMatrix4f("projection", projection);
  this->sprite_renderer.SetShader(spriteShader);
  this->resource_manager.LoadTexture("res/textures/mortis.png", true, "mortis");
}

void Game::Run() {

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  while (this->window_manager.GetIsRunning()) {

    float currentframe = glfwGetTime();
    deltaTime = currentframe - lastFrame;
    lastFrame = currentframe;

    this->window_manager.PollEvents();

    processInput();
    update();

    this->window_manager.ClearColor();

    render();

    this->window_manager.SwapBuffers();
    this->window_manager.CheckWindowStatus();
  }

  clean();
}

void Game::render() {
  sprite_renderer.DrawSprite(resource_manager.GetTexture("mortis"),
                             glm::vec2(400.0f, 300.0f), glm::vec2(100.0f, 100.0f), 0, glm::vec3(1.0f, 1.0f, 1.0f));
}

void Game::update() {}
void Game::processInput() {}
void Game::clean() {
  this->resource_manager.Clear();
  this->sprite_renderer.Clean();
  this->window_manager.Clean();
}
