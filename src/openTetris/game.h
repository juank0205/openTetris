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
  Game(int width, int height, const char *window_name);

  void Setup();
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
