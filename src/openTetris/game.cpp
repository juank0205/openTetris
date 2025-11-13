#include "game.h"
#include "board.h"
#include "game_constants.h"
#include "resource_manager.h"
#include "shader.h"
#include "shape.h"
#include "sprite_renderer.h"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <random>
#include <vector>

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
  generateNewShape();
}

void Game::Run() {

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  while (this->window_manager.GetIsRunning()) {

    float currentframe = glfwGetTime();
    deltaTime = currentframe - lastFrame;
    lastFrame = currentframe;

    this->window_manager.PollEvents();

    processInput(deltaTime);
    update(deltaTime);

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
  this->resource_manager.LoadTexture("res/textures/tile.png", true, "tile");
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
  board.Draw(sprite_renderer, resource_manager.GetTexture("tile"));
  currentShape.Draw(sprite_renderer, resource_manager.GetTexture("tile"));
}

void Game::update(float deltaTime) {
  fallTimer += deltaTime;
  if (fallTimer < fallInterval)
    return;

  currentShape.Update();
  fallTimer = 0.0f;

  auto shapeTiles = currentShape.GetTilePositions();
  if (board.CheckShapeMovement(shapeTiles)) {
    auto modifiedRows = board.PlaceShape(shapeTiles);
    int filledRow = board.CheckRows(modifiedRows);
    while (filledRow != BOARD_NO_ROW_CLEARED) {
      modifiedRows = board.UpdateBoard(filledRow);
      filledRow = board.CheckRows(modifiedRows);
    }
    generateNewShape();
  }
}

void Game::processInput(float deltaTime) {
  moveTimer += deltaTime;
  rotateTimer += deltaTime;

  if (window_manager.Keys[GLFW_KEY_RIGHT] && moveTimer >= moveCooldown) {
    currentShape.Move(SHAPE_DIRECTION_RIGHT);
    moveTimer = 0.0f;
  }
  if (window_manager.Keys[GLFW_KEY_LEFT] && moveTimer >= moveCooldown) {
    currentShape.Move(SHAPE_DIRECTION_LEFT);
    moveTimer = 0.0f;
  }

  if (window_manager.Keys[GLFW_KEY_X] && rotateTimer >= rotateCooldown) {
    currentShape.Rotate(SHAPE_DIRECTION_RIGHT);
    rotateTimer = 0.0f;
  }
  if (window_manager.Keys[GLFW_KEY_Z] && rotateTimer >= rotateCooldown) {
    currentShape.Rotate(SHAPE_DIRECTION_LEFT);
    rotateTimer = 0.0f;
  }
}

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<int> distr(0, 6);
void Game::generateNewShape() {
  int shapeIndex = distr(gen);
  ShapeType type = static_cast<ShapeType>(shapeIndex);

  int initialX = GRID_WIDTH / 2;
  int initialY = GRID_HEIGHT - 1; // top row (y increasing upwards)

  // Construct the new shape and set currentShape
  currentShape = Shape(type, initialX, initialY);
}

void Game::clean() {
  this->resource_manager.Clear();
  this->sprite_renderer.Clean();
  this->window_manager.Clean();
}
