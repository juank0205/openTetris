#pragma once

#include "program.h"

class Renderer {
public:
  Renderer();
  ~Renderer();

  void render();
  void setup();
  Program program;
};
