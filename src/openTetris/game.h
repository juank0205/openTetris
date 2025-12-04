#pragma once

#include "board.h"
#include "game_constants.h"
#include "resource_manager.h"
#include "shape.h"
#include "sprite_renderer.h"
#include "window_manager.h"
#include <array>

class Game {
public:
  /**
   * @brief Constructs the game with a given window size and title.
   *
   * @param width Width of the game window in pixels.
   * @param height Height of the game window in pixels.
   * @param window_name Title of the game window.
   */
  Game(int width, int height, const char *window_name);

  /**
   * @brief Sets up the game resources and initializes the first state.
   *
   * Loads textures, shaders, and prepares the board and initial shape.
   */
  void Setup();

  /**
   * @brief Runs the main game loop until the window is closed.
   *
   * Handles input, updates the game state, and renders each frame.
   */
  void Run();

private:
  ResourceManager resource_manager;
  GLFWwindow *window;
  SpriteRenderer sprite_renderer;
  Board board;
  Shape currentShape;

  void render();
  void update(double deltaTime);
  void processInput(double deltaTime);
  void clean();
  void generateNewShape();
  void drawBackground();
  void loadTextures();

  int width;
  int height;
  const char *window_name;
  std::array<bool, KEYS_ARRAY_SIZE> keys = {false};

  double fallTimer = 0.0F;
  double fallInterval = FALL_INTERVAL; // seconds per automatic fall

  double moveTimer = 0.0F;
  double moveCooldown = MOVE_COOLDOWN;

  double rotateTimer = 0.0F;
  double rotateCooldown = ROTATE_COOLDOWN;
};
