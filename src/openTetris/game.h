#pragma once

#include "resource_manager.h"
#include "shader.h"
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

  void render();
  void update();
  void processInput();
  void clean();
  void setupWorldCoordinates(float windowWidth, float windowHeight, ShaderProgram &shader);
  void drawBackground();
  void loadTextures();

  float width;
  float height;
  const char* window_name;
};
