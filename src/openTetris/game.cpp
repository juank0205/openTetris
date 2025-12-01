#include "game.h"
#include "board.h"
#include "game_constants.h"
#include "gl_debug.h"
#include "glm/fwd.hpp"
#include "resource_manager.h"
#include "shader.h"
#include "shape.h"
#include "sprite_renderer.h"
#include "window_manager.h"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <random>
#include <vector>

namespace {
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> distr(0, SHAPES_NUMBER);

void setup_world_coordinates(int windowWidth, int windowHeight,
                             ShaderProgram &shader);

void setup_world_coordinates(int windowWidth, int windowHeight,
                             ShaderProgram &shader) {
  const int scaleX = BOARD_WIDTH_PIXELS / GRID_WIDTH;
  const int scaleY = BOARD_HEIGHT_PIXELS / GRID_HEIGHT;
  const int offsetX = (windowWidth - BOARD_WIDTH_PIXELS) / 2;
  const int offsetY = (windowHeight - BOARD_HEIGHT_PIXELS) / 2;
  glm::mat4 view =
      glm::translate(glm::mat4(1.0F), glm::vec3(offsetX, offsetY, 0.0F));
  view = glm::scale(view, glm::vec3(scaleX, scaleY, 1.0F));
  const glm::mat4 projection =
      glm::ortho(0.0F, (float)windowWidth, 0.0F, (float)windowHeight);
  shader_program_set_matrix4(shader, "projection", projection,
                             true); // Uses shader
  shader_program_set_matrix4(shader, "view", view);
  unbind_shader_program();
}

} // namespace

Game::Game(int width, int height, const char *window_name) // NOLINT
    : width(width), height(height), window_name(window_name),
      currentShape(ShapeType::S, 0, 0) {}

void Game::Setup() {
  init_gl_context();
  this->window =
      create_window(this->width, this->height, this->window_name, keys);
  this->sprite_renderer.InitRenderData();

  this->resource_manager.LoadShader({.vertex = "res/shaders/sprite.vert",
                                     .fragment = "res/shaders/sprite.frag"},
                                    "sprite");
  ShaderProgram &spriteShader = this->resource_manager.GetShader("sprite");

  setup_world_coordinates(width, height, spriteShader);
  shader_program_set_integer(spriteShader, "image", 0, true); // Uses shader
  this->sprite_renderer.SetShader(spriteShader);
  loadTextures();
  generateNewShape();
}

void Game::Run() {

  double deltaTime = 0.0F;
  double lastFrame = 0.0F;

  while (check_window_status(window)) {
    const double currentframe = glfwGetTime();
    deltaTime = currentframe - lastFrame;
    lastFrame = currentframe;

    poll_events();
    processInput(deltaTime);
    update(deltaTime);
    clear_color();

    render();

    swap_buffers(window);
  }

  clean();
}

void Game::loadTextures() {
  this->resource_manager.LoadTexture("res/textures/mortis.png", true, "mortis");
  this->resource_manager.LoadTexture("res/textures/tile.png", true, "tile");
  this->resource_manager.LoadTexture("res/textures/background.jpg", true,
                                     "background");
  glGetError();
}

void Game::drawBackground() {
  sprite_renderer.DrawSprite(resource_manager.GetTexture("background"),
                             {.position = glm::vec2(0.0F),
                              .size = glm::vec2(GRID_WIDTH, GRID_HEIGHT),
                              .rotate = 0.0F});
  glGetError();
}

void Game::render() {
  drawBackground();
  board.Draw(sprite_renderer, resource_manager.GetTexture("tile"));
  currentShape.Draw(sprite_renderer, resource_manager.GetTexture("tile"));
  glGetError();
}

void Game::update(double deltaTime) {
  fallTimer += deltaTime;
  if (fallTimer < fallInterval) {
    return;
  }

  auto validator = [&](const std::vector<TilePosition> &positions) {
    return !board.CheckCollision(positions);
  };

  currentShape.Update(validator);
  fallTimer = 0.0F;

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

void Game::processInput(double deltaTime) {
  moveTimer += deltaTime;
  rotateTimer += deltaTime;

  auto validator = [&](const std::vector<TilePosition> &positions) {
    return !board.CheckCollision(positions); // you implement this
  };

  if (keys[GLFW_KEY_RIGHT] && moveTimer >= moveCooldown) {
    currentShape.Move(SHAPE_DIRECTION_RIGHT, validator);
    moveTimer = 0.0F;
  }
  if (keys[GLFW_KEY_LEFT] && moveTimer >= moveCooldown) {
    currentShape.Move(SHAPE_DIRECTION_LEFT, validator);
    moveTimer = 0.0F;
  }

  if (keys[GLFW_KEY_X] && rotateTimer >= rotateCooldown) {
    currentShape.Rotate(SHAPE_DIRECTION_RIGHT, validator);
    rotateTimer = 0.0F;
  }
  if (keys[GLFW_KEY_Z] && rotateTimer >= rotateCooldown) {
    currentShape.Rotate(SHAPE_DIRECTION_LEFT, validator);
    rotateTimer = 0.0F;
  }
}

void Game::generateNewShape() {
  const int shapeIndex = distr(gen);
  auto type = static_cast<ShapeType>(shapeIndex);

  const int initialX = GRID_WIDTH / 2;
  const int initialY = GRID_HEIGHT - 2; // top row (y increasing upwards)

  // Construct the new shape and set currentShape
  currentShape = Shape(type, initialX, initialY);
}

void Game::clean() {
  this->resource_manager.Clear();
  this->sprite_renderer.Clean();
  clean_gl_context();
}
