#pragma once

#include "board.h"
#include "resource_manager.h"
#include "shader.h"
#include "shape.h"
#include "sprite_renderer.h"
#include "window_manager.h"

class Game {
public:
  Game(float width, float height, const char *window_name);
  ~Game() {}

  void Setup();
  void Run();

private:
  ResourceManager resource_manager;
  WindowManager window_manager;
  SpriteRenderer sprite_renderer;
  Board board;
  Shape currentShape;

  void render();
  void update(float deltaTime);
  void processInput(float deltaTime);
  void clean();
  void generateNewShape();
  void setupWorldCoordinates(float windowWidth, float windowHeight,
                             ShaderProgram &shader);
  void drawBackground();
  void loadTextures();

  float width;
  float height;
  const char *window_name;
  float fallTimer = 0.0f;
  float fallInterval = 0.1f; // seconds per automatic fall

  float moveTimer = 0.0f;
  float moveCooldown = 0.1f;

  float rotateTimer = 0.0f;
  float rotateCooldown = 0.2f;
};
