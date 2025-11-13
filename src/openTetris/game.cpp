#include "game.h"
#include "resource_manager.h"
#include "shader.h"
#include "sprite_renderer.h"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

#define BOARD_WIDTH_PIXELS 250.0
#define BOARD_HEIGHT_PIXELS 450.0
#define GRID_HEIGHT 20
#define GRID_WIDTH 10

Game::Game(float width, float height, const char *window_name)
    : width(width), height(height), window_name(window_name) {}

void Game::Setup() {
  this->window_manager.CreateWindow(this->width, this->height,
                                    this->window_name);
  this->sprite_renderer.InitRenderData();

  this->resource_manager.LoadShader(
      "res/shaders/sprite.vert", "res/shaders/sprite.frag", nullptr, "sprite");
  ShaderProgram &spriteShader = this->resource_manager.GetShader("sprite");

  setupWorldCoordinates(width, height, spriteShader);
  spriteShader.SetInteger("image", 0, true); // Uses shader
                                             //
  this->sprite_renderer.SetShader(spriteShader);
  loadTextures();
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

void Game::setupWorldCoordinates(float windowWidth, float windowHeight,
                                 ShaderProgram &shader) {
  float scaleX = BOARD_WIDTH_PIXELS / GRID_WIDTH;
  float scaleY = BOARD_HEIGHT_PIXELS / GRID_HEIGHT;
  float offsetX = (windowWidth - BOARD_WIDTH_PIXELS) / 2.0f;
  float offsetY = (windowHeight - BOARD_HEIGHT_PIXELS) / 2.0f;
  glm::mat4 view =
      glm::translate(glm::mat4(1.0f), glm::vec3(offsetX, offsetY, 0.0f));
  view = glm::scale(view, glm::vec3(scaleX, scaleY, 1.0f));
  glm::mat4 projection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight);
  shader.SetMatrix4f("projection", projection, true); // Uses shader
  shader.SetMatrix4f("view", view);
  shader.Unbind();
}

void Game::loadTextures() {
  this->resource_manager.LoadTexture("res/textures/mortis.png", true, "mortis");
  this->resource_manager.LoadTexture("res/textures/background.jpg", true,
                                     "background");
}

void Game::drawBackground() {
  sprite_renderer.DrawSprite(resource_manager.GetTexture("background"),
                             glm::vec2(0.0f),
                             glm::vec2(GRID_WIDTH, GRID_HEIGHT), 0.0f);
}

void Game::render() {
  drawBackground();
  sprite_renderer.DrawSprite(resource_manager.GetTexture("mortis"),
                             glm::vec2(0.0f, 0.0f), glm::vec2(1.0f), 0);
  sprite_renderer.DrawSprite(resource_manager.GetTexture("mortis"),
                             glm::vec2(0.0f, 1.0f), glm::vec2(1.0f), 0);
  sprite_renderer.DrawSprite(resource_manager.GetTexture("mortis"),
                             glm::vec2(1.0f, 1.0f), glm::vec2(1.0f), 0);
  sprite_renderer.DrawSprite(resource_manager.GetTexture("mortis"),
                             glm::vec2(1.0f, 2.0f), glm::vec2(1.0f), 0);
}

void Game::update() {}
void Game::processInput() {}

void Game::clean() {
  this->resource_manager.Clear();
  this->sprite_renderer.Clean();
  this->window_manager.Clean();
}
